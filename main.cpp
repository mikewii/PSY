#include "Mainwindow.h"
#include <QApplication>
#include "Utils.h"
#include "Icon.hpp"

int main(int argc, char *argv[])
{
    Utils::initRandom();

    QApplication    app(argc, argv);
    MainWindow      win;

    app.setStyle("fusion");
    app.setWindowIcon(Icon(true));
    win.show();

    return app.exec();
}
