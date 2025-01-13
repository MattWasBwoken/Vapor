#include "MainWindow.h"
#include "../data/JsonItemLoader.h"
#include "../data/JsonItemSaver.h"
#include "AddItemView.h"
#include "EditItemView.h"
#include "../model/SearchItemVisitor.h"
#include "ViewRenderer.h"
#include "model/DLC.h"
#include "model/Software.h"
#include "model/Soundtrack.h"
#include "model/Videogame.h"
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
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
#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupMenus();
    setupToolBar();
    setupCentralWidget();
    setupStatusBar();
    populateItems();

    resize(1200, 800);
    setMinimumSize(400, 400);

    connect(viewRenderer, &ViewRenderer::itemSelected, this, &MainWindow::showItemDetails);
    connect(viewRenderer, &ViewRenderer::backToGridRequested, this, &MainWindow::handleBackToGrid);
    connect(viewRenderer, &ViewRenderer::editItemRequested, this, &MainWindow::handleModifyItem);
    connect(viewRenderer, &ViewRenderer::deleteItemRequested, this, &MainWindow::handleDeleteItem);
}

void MainWindow::setupMenus() {
    menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu(tr("File"));
    fileMenu->addAction(tr("Open"), this, &MainWindow::handleOpenFile);
    fileMenu->addAction(tr("Save"), this, &MainWindow::handleSave);
    fileMenu->addAction(tr("Save As"), this, &MainWindow::handleSaveAs);

    QMenu *itemMenu = menuBar->addMenu(tr("Item"));
    itemMenu->addAction(tr("Add"), this, &MainWindow::handleAddItem);
    itemMenu->addAction(tr("Edit"), this, &MainWindow::handleModifyItemFromMenu);
    itemMenu->addAction(tr("Delete"), this, &MainWindow::handleDeleteItemFromMenu);

    QMenu* viewMenu = menuBar->addMenu(tr("View"));
    QAction* gridViewAction = viewMenu->addAction(tr("Grid View"));
    QAction* listViewAction = viewMenu->addAction(tr("List View"));

    connect(gridViewAction, &QAction::triggered, this, [this]() {
        viewRenderer->setViewType(ViewType::Grid);
        updateStatus(tr("Switched to Grid View"));
        viewRenderer->render(items);
    });

    connect(listViewAction, &QAction::triggered, this, [this]() {
        viewRenderer->setViewType(ViewType::List);
        updateStatus(tr("Switched to List View"));
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

    QLabel* sortLabel = new QLabel("Sort by: ");
    sortComboBox = new QComboBox(this);
    sortComboBox->addItems({tr("Alphabetical"), tr("Recently added"), tr("Type")});
    connect(sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::handleSort);

    topToolBar->addWidget(searchBar);
    topToolBar->addWidget(filterComboBox);
    topToolBar->addAction(searchAction);

    QWidget* spacer = new QWidget(this);
    spacer->setFixedWidth(50);
    spacer->setFixedHeight(30);
    topToolBar->addWidget(spacer);
    topToolBar->addWidget(sortLabel);
    topToolBar->addWidget(sortComboBox);

    addToolBar(Qt::TopToolBarArea, topToolBar);
}

void MainWindow::setupCentralWidget() {
    centralWidget = new QStackedWidget(this);
    QScrollArea *scrollArea = new QScrollArea(this);
    viewRenderer = new ViewRenderer(scrollArea);

    scrollArea->setWidget(viewRenderer);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    viewRenderer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    centralWidget->addWidget(scrollArea);
    setCentralWidget(centralWidget);
    addItemView = new AddItemView(this, &items);
    centralWidget->addWidget(addItemView);
    editItemView = new EditItemView(this, &items);
    centralWidget->addWidget(editItemView);
    connect(addItemView, &AddItemView::itemAdded, this, &MainWindow::handleItemAdded);
    connect(addItemView, &AddItemView::backToGridRequested, this, &MainWindow::handleBackToGrid);
    connect(editItemView, &EditItemView::itemModified, this, &MainWindow::handleItemModified);
    connect(editItemView, &EditItemView::backToGridRequested, this, &MainWindow::handleBackToGrid);
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
    handleSort(0);
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
        if (!filePath.endsWith(".json", Qt::CaseInsensitive)) {
            filePath += ".json";
        }
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

void MainWindow::handleModifyItem(AbstractItem *item) {
    editItemView->setItem(item);
    centralWidget->setCurrentWidget(editItemView);
    updateStatus(tr("Editing item: %1").arg(item->getName()));
}

void MainWindow::handleModifyItemFromMenu() {
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Select Item to Edit"));
    QVBoxLayout dialogLayout;
    QListWidget itemList;
    for (const auto& item : items) {
        itemList.addItem(item->getName());
    }
    dialogLayout.addWidget(&itemList);
    QPushButton okButton(tr("OK"));
    QPushButton cancelButton(tr("Cancel"));
    QHBoxLayout buttonLayout;
    buttonLayout.addWidget(&okButton);
    buttonLayout.addWidget(&cancelButton);
    dialogLayout.addLayout(&buttonLayout);
    dialog.setLayout(&dialogLayout);
    connect(&okButton, &QPushButton::clicked, [&](){
        int selectedRow = itemList.currentRow();
        if(selectedRow >= 0 && selectedRow < items.size()){
            AbstractItem* selectedItem = items[selectedRow];
            handleModifyItem(selectedItem);
            dialog.accept();
        }
    });
    connect(&cancelButton, &QPushButton::clicked, [&](){
        dialog.reject();
    });
    dialog.exec();
}

void MainWindow::handleDeleteItem(AbstractItem *item) {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Deletion", "Are you really sure you want to delete '" + item->getName() + "'?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        unsigned int id = item->getId();
        auto it = std::find_if(items.begin(), items.end(), [id](AbstractItem* item) {
            return item->getId() == id;
        });
        if (it != items.end()) {
            QString name = (*it)->getName();
            items.erase(it);
            emit handleBackToGrid(false);
            viewRenderer->render(items);
            updateStatus(tr("Deleted item: %1").arg(item->getName()));
        }
    }
}

void MainWindow::handleDeleteItemFromMenu() {
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Select Item to Delete"));
    QVBoxLayout dialogLayout;
    QListWidget itemList;
    for (const auto& item : items) {
        itemList.addItem(item->getName());
    }
    dialogLayout.addWidget(&itemList);
    QPushButton okButton(tr("OK"));
    QPushButton cancelButton(tr("Cancel"));
    QHBoxLayout buttonLayout;
    buttonLayout.addWidget(&okButton);
    buttonLayout.addWidget(&cancelButton);
    dialogLayout.addLayout(&buttonLayout);
    dialog.setLayout(&dialogLayout);
    connect(&okButton, &QPushButton::clicked, [&](){
        int selectedRow = itemList.currentRow();
        if(selectedRow >= 0 && selectedRow < items.size()){
            AbstractItem* selectedItem = items[selectedRow];
            handleDeleteItem(selectedItem);
            dialog.accept();
        }
    });
    connect(&cancelButton, &QPushButton::clicked, [&](){
        dialog.reject();
    });
    dialog.exec();
}

void MainWindow::handleItemAdded(AbstractItem *item) {
    items.append(item);
    emit handleBackToGrid(false);
    viewRenderer->render(items);
    updateStatus(tr("Added item: %1").arg(item->getName()));
}

void MainWindow::handleItemModified(AbstractItem *item) {
    emit handleBackToGrid(false);
    viewRenderer->render(items);
    updateStatus(tr("Modified item: %1").arg(item->getName()));
}

void MainWindow::handleSort(int index) {
    if (index==0) {
        std::sort(items.begin(), items.end(), [](AbstractItem* a, AbstractItem* b) {
            return a->getName() < b->getName();
        });
    } else if (index==1) {
        std::sort(items.begin(), items.end(), [](AbstractItem* a, AbstractItem* b) {
            return a->getId() > b->getId();
        });
    } else if (index==2) {
        std::sort(items.begin(), items.end(), [](AbstractItem* a, AbstractItem* b) {
            int priorityIndexA = 0;
            int priorityIndexB = 0;
            if (dynamic_cast<Software*>(a)) {
                priorityIndexA = 1;
            } else if (dynamic_cast<DLC*>(a)) {
                priorityIndexA = 3;
            } else if (dynamic_cast<Soundtrack*>(a)) {
                priorityIndexA = 2;
            } else if (dynamic_cast<Videogame*>(a)) {
                priorityIndexA = 4;
            }
            if (dynamic_cast<Software*>(b)) {
                priorityIndexB = 1;
            } else if (dynamic_cast<DLC*>(b)) {
                priorityIndexB = 3;
            } else if (dynamic_cast<Soundtrack*>(b)) {
                priorityIndexB = 2;
            } else if (dynamic_cast<Videogame*>(b)) {
                priorityIndexB = 4;
            }
            return priorityIndexA > priorityIndexB;
        });
    }
    viewRenderer->render(items);
    QString sortType = sortComboBox->itemText(index);
    updateStatus(tr("Items sorted by: %1").arg(sortType));
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

void MainWindow::handleBackToGrid(bool showMessage) {
    centralWidget->setCurrentWidget(centralWidget->widget(0));
    viewRenderer->setViewType(ViewType::Grid);
    viewRenderer->render(items);
    if (showMessage) {
        updateStatus(tr("Back to Grid View"));
    }
}
