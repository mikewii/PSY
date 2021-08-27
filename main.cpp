#include "CMainwindow.h"
#include <QApplication>
#include "CUtils.h"

int main(int argc, char *argv[])
{
    Utils::initRandom();

    QApplication a(argc, argv);
    a.setStyle("windows");
    MainWindow w;
    w.show();
    return a.exec();
}
