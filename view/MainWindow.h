#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QStackedWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QListView>
#include <QTableWidget>
#include <QString>
#include <QVector>
#include <QFileDialog>
#include <QMessageBox>
#include "../model/AbstractItem.h"
#include "ViewRenderer.h"
#include "AddItemView.h"
#include "EditItemView.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QMenuBar *menuBar;
    QToolBar *topToolBar;
    QStatusBar *statusBar;
    QStackedWidget *centralWidget;
    QLineEdit *searchBar;
    QComboBox *filterComboBox;

    QVector<AbstractItem*> items;
    ViewRenderer* viewRenderer;
    AddItemView *addItemView;
    EditItemView *editItemView;
    QString currentFilePath;

    void setupMenus();
    void setupToolBar();
    void setupCentralWidget();
    void setupStatusBar();
    void populateItems();

signals:
    void searchRequested(const QString &searchText, const QString &filter);
    void itemSelected(AbstractItem *item);

private slots:
    void handleSearch();
    void handleAddItem();
    void handleModifyItem(AbstractItem *item);
    void handleModifyItemFromMenu();
    void handleDeleteItem(AbstractItem *item);
    void handleDeleteItemFromMenu();
    void updateStatus(const QString &message);
    void showItemDetails(AbstractItem* item);
    void handleItemAdded(AbstractItem *item);
    void handleItemModified(AbstractItem *item);
    void handleBackToGrid(bool showMessage);
    void handleOpenFile();
    void handleSave();
    void handleSaveAs();
};

#endif
