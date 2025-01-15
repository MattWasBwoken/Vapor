#include "MainWindow.h"
#include "data/JsonItemLoader.h"
#include "data/JsonItemSaver.h"
#include "model/SearchItemVisitor.h"
#include "model/DLC.h"
#include "model/Software.h"
#include "model/Soundtrack.h"
#include "model/Videogame.h"
#include <QAction>
#include <QBoxLayout>
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
#include <QListWidget>
#include <QPushButton>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    setupMenus();
    setupToolBar();
    setupCentralWidget();
    setupStatusBar();
    populateItems();

    resize(1200, 800);
    setMinimumSize(600, 400);

    connect(viewRenderer, &ViewRenderer::itemSelected, this, &MainWindow::showItemDetails);
    connect(viewRenderer, &ViewRenderer::backToGridRequested, this, &MainWindow::handleBackToGrid);
    connect(viewRenderer, &ViewRenderer::editItemRequested, this, &MainWindow::handleModifyItem);
    connect(viewRenderer, &ViewRenderer::deleteItemRequested, this, &MainWindow::handleDeleteItem);
    searchTimer = new QTimer(this);
    searchTimer->setSingleShot(true);
    connect(searchTimer, &QTimer::timeout, this, &MainWindow::handleSearch);
}

void MainWindow::setupMenus() {
    menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu(tr("File"));

    QAction* openAction = fileMenu->addAction(tr("Open"));
    openAction->setIcon(QIcon(":/assets/icon_open.png"));
    connect(openAction, &QAction::triggered, this, &MainWindow::handleOpenFile);
    QAction* saveAction = fileMenu->addAction(tr("Save"));
    saveAction->setIcon(QIcon(":/assets/icon_save.png"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::handleSave);
    QAction* saveAsAction = fileMenu->addAction(tr("Save As"));
    saveAsAction->setIcon(QIcon(":/assets/icon_saveas.png"));
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::handleSaveAs);

    QMenu *itemMenu = menuBar->addMenu(tr("Item"));

    QAction* addAction = itemMenu->addAction(tr("Add"));
    addAction->setIcon(QIcon(":/assets/icon_add.png"));
    connect(addAction, &QAction::triggered, this, &MainWindow::handleAddItem);
    QAction* editAction = itemMenu->addAction(tr("Edit"));
    editAction->setIcon(QIcon(":/assets/icon_edit.png"));
    connect(editAction, &QAction::triggered, this, &MainWindow::handleModifyItemFromMenu);
    QAction* deleteAction = itemMenu->addAction(tr("Delete"));
    deleteAction->setIcon(QIcon(":/assets/icon_delete.png"));
    connect(deleteAction, &QAction::triggered, this, &MainWindow::handleDeleteItemFromMenu);

    QMenu* viewMenu = menuBar->addMenu(tr("View"));
    QAction* gridViewAction = viewMenu->addAction(tr("Grid View"));
    gridViewAction->setIcon(QIcon(":/assets/icon_gridview.png"));
    QAction* listViewAction = viewMenu->addAction(tr("List View"));
    listViewAction->setIcon(QIcon(":/assets/icon_listview.png"));

    connect(gridViewAction, &QAction::triggered, this, [this]() {
        centralWidget->setCurrentWidget(centralWidget->widget(0));
        viewRenderer->setViewType(ViewType::Grid);
        updateStatus(tr("Switched to Grid View"));
        viewRenderer->render(items);
    });

    connect(listViewAction, &QAction::triggered, this, [this]() {
        centralWidget->setCurrentWidget(centralWidget->widget(0));
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
    searchBar->setStyleSheet("QLineEdit {padding: 2px 5px; margin: 5px; background-image: url(:/assets/icon_search.png); background-repeat: no-repeat; background-position: right center;"
                             "background-origin: content; border: 1px solid #ccc; border-radius: 5px; } QLineEdit:focus { border-color: #66afe9; outline: 0; }");
    connect(searchBar, &QLineEdit::textChanged, this, [this](){
        if (searchTimer->isActive()) {
            searchTimer->stop();
        }
        searchTimer->start(300);
    });
    filterComboBox = new QComboBox(this);
    filterComboBox->addItems({tr("All"), tr("Software"), tr("Videogame"), tr("DLC"), tr("Soundtrack")});
    connect(filterComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::handleSearch);

    QLabel* sortLabel = new QLabel("Sort by: ");
    sortComboBox = new QComboBox(this);
    sortComboBox->addItems({tr("Alphabetical"), tr("Recently added"), tr("Type")});
    connect(sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::handleSort);

    topToolBar->addWidget(searchBar);
    topToolBar->addWidget(filterComboBox);

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

    QScrollArea *addScrollArea = new QScrollArea(this);
    addItemView = new AddItemView(this, &items);
    addScrollArea->setWidget(addItemView);
    addScrollArea->setWidgetResizable(true);
    addScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    addScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    centralWidget->addWidget(addScrollArea);

    QScrollArea *editScrollArea = new QScrollArea(this);
    editItemView = new EditItemView(this, &items);
    editScrollArea->setWidget(editItemView);
    editScrollArea->setWidgetResizable(true);
    editScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    editScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    centralWidget->addWidget(editScrollArea);

    setCentralWidget(centralWidget);

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
    viewRenderer->render(items);
    handleSort(sortComboBox->currentIndex());
    updateStatus(tr("Loaded %1 items from default library").arg(items.size()));
}

void MainWindow::handleSearch() {
    if (searchTimer->isActive()) {
        searchTimer->stop();
        searchTimer->start(300);
    }

    const QString searchText = searchBar->text();
    const QString filter = filterComboBox->currentText();

    if (viewRenderer->getViewType() == ViewType::Details) {
        viewRenderer->setViewType(ViewType::Grid);
    }

    SearchItemVisitor visitor(searchText, filter);
    for (const auto& item : items) {
        item->accept(&visitor);
    }

    QVector<const AbstractItem*> constResults = visitor.getResults();
    QVector<AbstractItem*> filteredItems;
    for (const AbstractItem* constItem : constResults) {
        filteredItems.append(const_cast<AbstractItem*>(constItem));
    }

    viewRenderer->render(filteredItems);
    updateStatus(tr("Search performed with filter: %1").arg(filter));
}

void MainWindow::handleOpenFile() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open JSON File"), "", tr("JSON Files (*.json)"));
    if (!filePath.isEmpty()) {
        currentFilePath = filePath;
        QVector<AbstractItem*> loadedItems = JsonItemLoader::loadItemsFromJson(filePath);
        if (!loadedItems.isEmpty()) {
            for (AbstractItem* item : items) {
                delete item;
            }
            items.clear();
            items = loadedItems;
            viewRenderer->render(items);
            handleSort(sortComboBox->currentIndex());
            updateStatus(tr("Loaded %1 items from file: %2").arg(items.size()).arg(filePath));
        } else {
            updateStatus(tr("Failed to load items from file: %1").arg(filePath));
            QMessageBox::warning(this, tr("Error"), tr("Failed to load items from the selected file."));
        }
    }
}

void MainWindow::handleSave() {
    if (currentFilePath.isEmpty()) {
        handleSaveAs();
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
            currentFilePath = filePath;
            updateStatus(tr("Saved items to file: %1").arg(filePath));
        } else {
            updateStatus(tr("Failed to save items to file: %1").arg(filePath));
            QMessageBox::warning(this, tr("Error"), tr("Failed to save items to the selected file."));
        }
    }
}

void MainWindow::handleAddItem() {
    addItemView->resetFields();
    centralWidget->setCurrentWidget(centralWidget->widget(1));
    updateStatus(tr("Adding new item"));
}

void MainWindow::handleModifyItem(AbstractItem *item) {
    editItemView->setItem(item);
    centralWidget->setCurrentWidget(centralWidget->widget(2));
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
    handleSort(sortComboBox->currentIndex());
    viewRenderer->render(items);
    updateStatus(tr("Added item: %1").arg(item->getName()));
}

void MainWindow::handleItemModified(AbstractItem *item) {
    emit handleBackToGrid(false);
    handleSort(sortComboBox->currentIndex());
    viewRenderer->render(items);
    updateStatus(tr("Modified item: %1").arg(item->getName()));
}

void MainWindow::handleSort(int index) {
    if (index==0) {
        std::sort(items.begin(), items.end(), [](AbstractItem* a, AbstractItem* b) {
            return a->getName().toLower() < b->getName().toLower();
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
