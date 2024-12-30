#include "mainwindow.h"
#include <QApplication>
#include <QHBoxLayout>

// Costruttore della classe
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Vapor - Digital Library");
    resize(1024, 768);

    // Menubar
    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *fileMenu = menuBar->addMenu("File");
    fileMenu->addAction("Apri", this, &MainWindow::openFile);
    fileMenu->addAction("Salva", this, &MainWindow::saveFile);
    fileMenu->addAction("Salva con nome", this, &MainWindow::saveFileAs);

    QMenu *itemMenu = menuBar->addMenu("Item");
    itemMenu->addAction("Aggiungi", this, &MainWindow::addItem);
    itemMenu->addAction("Modifica", this, &MainWindow::editItem);
    itemMenu->addAction("Elimina", this, &MainWindow::deleteItem);

    QMenu *viewMenu = menuBar->addMenu("View");
    viewMenu->addAction("Vista Griglia", this, &MainWindow::switchToGridView);
    viewMenu->addAction("Vista Elenco", this, &MainWindow::switchToListView);

    // Toolbar
    toolBar = new QToolBar(this);
    addToolBar(toolBar);

    toolBar->addAction(QIcon(":/icons/new_file.png"), "Nuovo", this, &MainWindow::newFile);
    toolBar->addAction(QIcon(":/icons/open_file.png"), "Apri", this, &MainWindow::openFile);
    toolBar->addAction(QIcon(":/icons/save.png"), "Salva", this, &MainWindow::saveFile);
    toolBar->addAction(QIcon(":/icons/add_item.png"), "Aggiungi", this, &MainWindow::addItem);
    toolBar->addAction(QIcon(":/icons/edit_item.png"), "Modifica", this, &MainWindow::editItem);
    toolBar->addAction(QIcon(":/icons/delete_item.png"), "Elimina", this, &MainWindow::deleteItem);

    // Status bar
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    // Central Widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Search Section
    QWidget *searchWidget = new QWidget(this);
    QVBoxLayout *searchLayout = new QVBoxLayout(searchWidget);

    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Cerca...");

    typeFilter = new QComboBox(this);
    typeFilter->addItem("Tutti");
    typeFilter->addItem("Videogame");
    typeFilter->addItem("DLC");
    typeFilter->addItem("Soundtrack");
    typeFilter->addItem("Software");

    searchLayout->addWidget(new QLabel("Ricerca:"));
    searchLayout->addWidget(searchBar);
    searchLayout->addWidget(typeFilter);

    // Central Area
    stackedWidget = new QStackedWidget(this);

    QWidget *homePage = new QWidget(this);
    QVBoxLayout *homeLayout = new QVBoxLayout(homePage);

    QLabel *homeTitle = new QLabel("Home - Tutti i prodotti", this);
    itemList = new QListWidget(this);

    homeLayout->addWidget(homeTitle);
    homeLayout->addWidget(itemList);

    stackedWidget->addWidget(homePage);

    // Layout Integration
    QHBoxLayout *contentLayout = new QHBoxLayout;
    contentLayout->addWidget(searchWidget);
    contentLayout->addWidget(stackedWidget, 1);

    mainLayout->addLayout(contentLayout);
}

// Implementazione degli slot
void MainWindow::openFile() {
    statusBar->showMessage("Apertura file...");
}

void MainWindow::saveFile() {
    statusBar->showMessage("Salvataggio file...");
}

void MainWindow::saveFileAs() {
    statusBar->showMessage("Salvataggio file con nome...");
}

void MainWindow::addItem() {
    statusBar->showMessage("Aggiunta elemento...");
}

void MainWindow::editItem() {
    statusBar->showMessage("Modifica elemento...");
}

void MainWindow::deleteItem() {
    statusBar->showMessage("Eliminazione elemento...");
}

void MainWindow::switchToGridView() {
    statusBar->showMessage("Vista Griglia attivata...");
}

void MainWindow::switchToListView() {
    statusBar->showMessage("Vista Elenco attivata...");
}

void MainWindow::newFile() {
    statusBar->showMessage("Nuovo file creato...");
}
