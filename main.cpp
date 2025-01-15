#include "view/MainWindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setStyle(QStyleFactory::create("Fusion"));

    app.setStyleSheet(
        "QMainWindow { background-color: #252525; }"
        "QWidget { color: #eee; }"
        "QMenuBar { background-color: #232323; color: #eee; }"
        "QMenuBar::item { background-color: #232323; color: #eee; }"
        "QMenuBar::item::selected { background-color: #202020; }"
        "QMenu { background-color: #232323; color: #eee; }"
        "QMenu::item { background-color: #232323; color: #eee; }"
        "QMenu::item::selected { background-color: #202020; }"
        "QStatusBar { background-color: #232323; color: #eee; }"
        "QToolBar { background-color: #232323; color: #eee; border: none; }"
        "QToolButton { background-color: #232323; color: #eee; }"
        "QToolButton:hover { background-color: #202020; color: #eee; }"
        "QLineEdit { background-color: #303030; color: #eee; border: 1px solid #777; border-radius: 5px; padding: 2px; }"
        "QTextEdit { background-color: #303030; color: #eee; border: 1px solid #777; border-radius: 5px; padding: 2px; }"
        "QComboBox { background-color: #303030; color: #eee; border: 0px; border-radius: 5px; }"
        "QComboBox::drop-down { border: 0px; }"
        "QComboBox QAbstractItemView { background-color: #303030; color: #eee; border: 0px; border-radius: 5px; }"
        "QCheckBox { color: #eee; }"
        "QCheckBox::indicator { background-color: #303030; border: 1px solid #777; width: 15px; height: 15px; border-radius: 3px; }"
        "QCheckBox::indicator:checked { background-color: #2196F3; border: 1px solid #2196F3; image: url(:/assets/icon_check.png); }"
        "QPushButton { background-color: #303030; color: #eee; border: 0px; padding: 5px 10px; border-radius: 5px; }"
        "QPushButton:hover { background-color: #666; }"
        "QScrollArea { border: none; }"
        "QScrollBar:vertical { border: none; background: #303030; width: 10px; margin: 0px 0px 0px 0px; }"
        "QScrollBar::handle:vertical { background: #555; min-height: 20px; border-radius: 5px;}"
        "QScrollBar::add-line:vertical { border: none; background: none; }"
        "QScrollBar::sub-line:vertical { border: none; background: none; }"
        "QScrollBar:horizontal { border: none; background: #303030; height: 10px; margin: 0px 0px 0px 0px; }"
        "QScrollBar::handle:horizontal { background: #555; min-width: 20px; border-radius: 5px;}"
        "QScrollBar::add-line:horizontal { border: none; background: none; }"
        "QScrollBar::sub-line:horizontal { border: none; background: none; }"
        );

    QApplication::setWindowIcon(QIcon(":/assets/vapor_logo.png"));
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
