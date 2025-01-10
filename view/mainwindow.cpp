#include "MainWindow.h"
#include "../data/JsonItemLoader.h"
#include "../model/ItemFactory.h"
#include "../model/SearchItemVisitor.h"
#include "ViewRenderer.h"
#include <QAction>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCoreApplication>
#include <QDir>
#include <QScrollArea>

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
    fileMenu->addAction(tr("Open"), this, []() { /* TODO: Add open functionality */ });
    fileMenu->addAction(tr("Save"), this, []() { /* TODO: Add save functionality */ });
    fileMenu->addAction(tr("Save As"), this, []() { /* TODO: Add save-as functionality */ });

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
    QScrollArea *scrollArea = new QScrollArea(this);
    viewRenderer = new ViewRenderer(scrollArea); // Attach ViewRenderer to scrollArea

    // Configure the scroll area for vertical scrolling only
    scrollArea->setWidget(viewRenderer);
    scrollArea->setWidgetResizable(true); // Resize content dynamically
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Disable horizontal scrolling
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);   // Enable vertical scrolling

    // Ensure the ViewRenderer widget expands to the full width of the scroll area
    viewRenderer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    setCentralWidget(scrollArea); // Set scrollArea as the central widget
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
    updateStatus(tr("Loaded %1 items from resources").arg(items.size()));
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

void MainWindow::handleAddItem() {
    AbstractItem *newItem = ItemFactory::createItem(this);
    if (newItem) {
        items.append(newItem);
        emit itemAdded(newItem);
        viewRenderer->render(items);
        updateStatus(tr("Added new item: %1").arg(newItem->getName()));
    } else {
        updateStatus(tr("Item creation canceled"));
    }
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
    viewRenderer->setViewType(ViewType::Grid);
    viewRenderer->render(items);
    updateStatus(tr("Back to Grid View"));

}
