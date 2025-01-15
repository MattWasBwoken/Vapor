#include "view/MainWindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QStyleFactory>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setStyle(QStyleFactory::create("Fusion"));
    QFile stylesheet(":/assets/style.qss");
    stylesheet.open(QFile::ReadOnly);
    app.setStyleSheet(QLatin1String(stylesheet.readAll()));

    QApplication::setWindowIcon(QIcon(":/assets/vapor_logo.png"));
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
