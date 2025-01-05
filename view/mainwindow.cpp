#include "MainWindow.h"
#include <QAction>
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupMenus();
    setupToolBar();
    setupCentralWidget();
    setupStatusBar();
    populateItems();

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

    QMenu *viewMenu = menuBar->addMenu(tr("View"));
    viewMenu->addAction(tr("Grid View"), this, []() { /* TODO: Add grid view functionality */ });
    viewMenu->addAction(tr("List View"), this, []() { /* TODO: Add list view functionality */ });

    setMenuBar(menuBar);
}

void MainWindow::setupToolBar() {
    topToolBar = new QToolBar(this);
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText(tr("Search..."));
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
    setCentralWidget(centralWidget);
}

void MainWindow::setupStatusBar() {
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
}

void MainWindow::populateItems() {
    // Example population; replace with dynamic loading if necessary
    items.append(new AbstractItem(1, "Example Item", "Description"));
}

void MainWindow::handleSearch() {
    const QString searchText = searchBar->text();
    const QString filter = filterComboBox->currentText();
    emit searchRequested(searchText, filter);
    updateStatus(tr("Search performed with filter: %1").arg(filter));
}

void MainWindow::handleAddItem() {
    // Example implementation
    AbstractItem *newItem = new AbstractItem(999, "New Item", "Description");
    emit itemAdded(newItem);
}

void MainWindow::handleModifyItem(AbstractItem *item) {
    // Placeholder for item modification logic
    emit itemModified(item);
}

void MainWindow::handleDeleteItem(unsigned int id) {
    emit itemDeleted(id);
}

void MainWindow::updateStatus(const QString &message) {
    statusBar->showMessage(message, 5000);
}
