#include "MainWindow.h"
#include "../data/JsonItemLoader.h"
#include "../data/JsonItemSaver.h"
#include "AddItemView.h"
#include "../model/SearchItemVisitor.h"
#include "ViewRenderer.h"
#include <QAction>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCoreApplication>
#include <QDir>
#include <QScrollArea>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupMenus();
    setupToolBar();
    setupCentralWidget();
    setupStatusBar();
    populateItems();

    resize(1200, 800);
    setMinimumSize(400, 400);

    connect(this, &MainWindow::itemAdded, this, [this](AbstractItem *item) {
        items.append(item);
        updateStatus(tr("Item added: %1").arg(item->getName()));
    });

    connect(this, &MainWindow::itemModified, this, [this](AbstractItem *item) {
        updateStatus(tr("Item modified: %1").arg(item->getName()));
    });

    connect(this, &MainWindow::itemDeleted, this, [this](unsigned int id) {
        auto it = std::find_if(items.begin(), items.end(), [id](AbstractItem *item) {
            return item->getId() == id;
        });
        if (it != items.end()) {
            QString name = (*it)->getName();
            items.erase(it);
            updateStatus(tr("Item deleted: %1").arg(name));
        }
    });

    connect(viewRenderer, &ViewRenderer::itemSelected, this, &MainWindow::showItemDetails);
    connect(viewRenderer, &ViewRenderer::backToGridRequested, this, &MainWindow::handleBackToGrid);
}

void MainWindow::setupMenus() {
    menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu(tr("File"));
    fileMenu->addAction(tr("Open"), this, &MainWindow::handleOpenFile);
    fileMenu->addAction(tr("Save"), this, &MainWindow::handleSave);
    fileMenu->addAction(tr("Save As"), this, &MainWindow::handleSaveAs);

    QMenu *itemMenu = menuBar->addMenu(tr("Item"));
    itemMenu->addAction(tr("Add"), this, &MainWindow::handleAddItem);
    itemMenu->addAction(tr("Modify"), this, []() { /* TODO: Add modify item dialog */ });
    itemMenu->addAction(tr("Delete"), this, []() { /* TODO: Add delete item dialog */ });

    QMenu* viewMenu = menuBar->addMenu(tr("View"));
    QAction* gridViewAction = viewMenu->addAction(tr("Grid View"));
    QAction* listViewAction = viewMenu->addAction(tr("List View"));

    connect(gridViewAction, &QAction::triggered, this, [this]() {
        viewRenderer->setViewType(ViewType::Grid); // Use enum
        viewRenderer->render(items);
    });

    connect(listViewAction, &QAction::triggered, this, [this]() {
        viewRenderer->setViewType(ViewType::List); // Use enum
        viewRenderer->render(items);
    });

    setMenuBar(menuBar);
}

void MainWindow::setupToolBar() {
    topToolBar = new QToolBar(this);
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText(tr("Search..."));
    connect(searchBar, &QLineEdit::returnPressed, this, &MainWindow::handleSearch);
    filterComboBox = new QComboBox(this);
    filterComboBox->addItems({tr("All"), tr("Software"), tr("Videogame"), tr("DLC"), tr("Soundtrack")});

    QAction *searchAction = new QAction(tr("Search"), this);
    connect(searchAction, &QAction::triggered, this, &MainWindow::handleSearch);

    topToolBar->addWidget(searchBar);
    topToolBar->addWidget(filterComboBox);
    topToolBar->addAction(searchAction);

    addToolBar(Qt::TopToolBarArea, topToolBar);
}

void MainWindow::setupCentralWidget() {
    centralWidget = new QStackedWidget(this);
    QScrollArea *scrollArea = new QScrollArea(this);
    viewRenderer = new ViewRenderer(scrollArea); // Attach ViewRenderer to scrollArea

    // Configure the scroll area for vertical scrolling only
    scrollArea->setWidget(viewRenderer);
    scrollArea->setWidgetResizable(true); // Resize content dynamically
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Disable horizontal scrolling
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);   // Enable vertical scrolling

    // Ensure the ViewRenderer widget expands to the full width of the scroll area
    viewRenderer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    centralWidget->addWidget(scrollArea);
    setCentralWidget(centralWidget);
    addItemView = new AddItemView(this);
    centralWidget->addWidget(addItemView);
    connect(addItemView, &AddItemView::itemAdded, this, &MainWindow::handleItemAdded);
    connect(addItemView, &AddItemView::backToGridRequested, this, &MainWindow::handleBackToGrid);
}

void MainWindow::setupStatusBar() {
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
}

void MainWindow::populateItems() {
    QString filePath = ":/data/library.json";

    QFile file(filePath);
    if (!file.exists()) {
        qWarning() << "File does not exist in resources:" << filePath;
        updateStatus(tr("Failed to load items: File not found in resources"));
        return;
    }

    items = JsonItemLoader::loadItemsFromJson(filePath);
    updateStatus(tr("Loaded %1 items from default library").arg(items.size()));
    viewRenderer->render(items);
}

void MainWindow::handleSearch() {
    const QString searchText = searchBar->text();
    const QString filter = filterComboBox->currentText();

    if (viewRenderer->getViewType() == ViewType::Details) {
        viewRenderer->setViewType(ViewType::Grid);
    }

    // Filter items using the SearchItemVisitor
    SearchItemVisitor visitor(searchText, filter);
    for (const auto& item : items) {
        item->accept(&visitor);
    }

    // Convert QVector<const AbstractItem*> to QVector<AbstractItem*>
    QVector<const AbstractItem*> constResults = visitor.getResults();
    QVector<AbstractItem*> filteredItems;
    for (const AbstractItem* constItem : constResults) {
        filteredItems.append(const_cast<AbstractItem*>(constItem));
    }

    // Call render with the converted QVector<AbstractItem*>
    viewRenderer->render(filteredItems);

    updateStatus(tr("Search performed with filter: %1").arg(filter));
}

void MainWindow::handleOpenFile() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open JSON File"), "", tr("JSON Files (*.json)"));
    if (!filePath.isEmpty()) {
        currentFilePath = filePath; // keep json path for saving
        QVector<AbstractItem*> loadedItems = JsonItemLoader::loadItemsFromJson(filePath);
        if (!loadedItems.isEmpty()) {
            // Clear existing items
            for (AbstractItem* item : items) {
                delete item;
            }
            items.clear();
            //assign loaded items
            items = loadedItems;
            viewRenderer->render(items);
            updateStatus(tr("Loaded %1 items from file: %2").arg(items.size()).arg(filePath));
        } else {
            updateStatus(tr("Failed to load items from file: %1").arg(filePath));
            QMessageBox::warning(this, tr("Error"), tr("Failed to load items from the selected file."));
        }
    }
}

void MainWindow::handleSave() {
    if (currentFilePath.isEmpty()) {
        handleSaveAs(); // if no file is open, handleSaveAs
    } else {
        if (JsonItemSaver::saveItemsToJson(items, currentFilePath)) {
            updateStatus(tr("Saved items to file: %1").arg(currentFilePath));
        } else {
            updateStatus(tr("Failed to save items to file: %1").arg(currentFilePath));
            QMessageBox::warning(this, tr("Error"), tr("Failed to save items to the selected file."));
        }
    }
}

void MainWindow::handleSaveAs() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save JSON File"), "", tr("JSON Files (*.json)"));
    if (!filePath.isEmpty()) {
        if (JsonItemSaver::saveItemsToJson(items, filePath)) {
            currentFilePath = filePath; // update currentFilePath
            updateStatus(tr("Saved items to file: %1").arg(filePath));
        } else {
            updateStatus(tr("Failed to save items to file: %1").arg(filePath));
            QMessageBox::warning(this, tr("Error"), tr("Failed to save items to the selected file."));
        }
    }
}

void MainWindow::handleAddItem() {
    addItemView->resetFields();
    centralWidget->setCurrentWidget(addItemView);
    updateStatus(tr("Adding new item"));
}

void MainWindow::handleItemAdded(AbstractItem *item) {
    items.append(item);
    updateStatus(tr("Added item: %1").arg(item->getName()));
    viewRenderer->render(items);
    centralWidget->setCurrentWidget(centralWidget->widget(0));
}

void MainWindow::handleModifyItem(AbstractItem *item) {
    // Placeholder for item modification logic
    emit itemModified(item);
    viewRenderer->render(items);
    updateStatus(tr("Modified item: %1").arg(item->getName()));
}

void MainWindow::handleDeleteItem(unsigned int id) {
    auto it = std::find_if(items.begin(), items.end(), [id](AbstractItem* item) {
        return item->getId() == id;
    });
    if (it != items.end()) {
        QString name = (*it)->getName();
        items.erase(it);

        // Call render to update the view
        viewRenderer->render(items);
        emit itemDeleted(id);
        updateStatus(tr("Deleted item: %1").arg(name));
    }
}

void MainWindow::updateStatus(const QString &message) {
    statusBar->showMessage(message, 5000);
}

void MainWindow::showItemDetails(AbstractItem* item){
    viewRenderer->setViewType(ViewType::Details);
    QVector<AbstractItem*> selectedItem;
    selectedItem.push_back(item);
    viewRenderer->render(selectedItem);
    updateStatus(tr("Opening details of item: %1").arg(item->getName()));
}

void MainWindow::handleBackToGrid() {
    centralWidget->setCurrentWidget(centralWidget->widget(0));
    viewRenderer->setViewType(ViewType::Grid);
    viewRenderer->render(items);
    updateStatus(tr("Back to Grid View"));
}
