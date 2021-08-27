#include "Mainwindow.h"
#include <QApplication>
#include "Utils.h"

int main(int argc, char *argv[])
{
    Utils::initRandom();

    QApplication a(argc, argv);
    a.setStyle("windows");
    MainWindow w;
    w.show();
    return a.exec();
}
