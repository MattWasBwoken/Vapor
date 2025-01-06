#include "view/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(":/assets/vapor_logo.png"));
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
