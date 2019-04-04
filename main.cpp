#include "mainwindow.h"
#include "test.h"
#include "computer_manager.h"
#include <QApplication>
#include <QWidget>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.showMaximized();

    return app.exec();
}
