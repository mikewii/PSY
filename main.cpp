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

#ifdef __linux__
    app.setWindowIcon(Icon(true));
#endif

    win.show();

    return app.exec();
}
