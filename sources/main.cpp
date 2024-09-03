#include "controller.h"
#include <QApplication>
#include <QStyleFactory>


int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    application.setStyle(QStyleFactory::create("Fusion"));
    NoterController mainWindow;
    mainWindow.show();
    return application.exec();
}
