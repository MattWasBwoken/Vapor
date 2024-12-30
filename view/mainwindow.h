#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QStackedWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void openFile();
    void saveFile();
    void saveFileAs();
    void addItem();
    void editItem();
    void deleteItem();
    void switchToGridView();
    void switchToListView();
    void newFile();

private:
    // Dichiarazioni dei componenti principali
    QMenuBar *menuBar;
    QToolBar *toolBar;
    QStatusBar *statusBar;
    QStackedWidget *stackedWidget;
    QLineEdit *searchBar;
    QComboBox *typeFilter;
    QListWidget *itemList;
};

#endif
