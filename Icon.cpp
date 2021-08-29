#include "Icon.hpp"
#include <QPainter>
#include "Utils.h"

Icon::Icon()
{
    this->generate();
}

void Icon::generate()
{
    QPixmap     pix(this->width, this->height);
    QPainter    painter;
    QPen        pen;


    painter.begin(&pix);

    for ( int y = 0; y < pix.height(); y++ )
    {
        QLine   line1, line2;
        int     col1    = Utils::getRandom(70, 200); // grey
        int     col2    = Utils::getRandom(70, 200);
        int     split   = Utils::getRandom(1, pix.width() - 2);


        line1 = {0, y, split, y};
        line2 = {split, y, pix.width() - 1, y};

        pen.setColor({col1,col1,col1});
        painter.setPen(pen);
        painter.drawLine(line1);

        pen.setColor({col2,col2,col2});
        painter.setPen(pen);
        painter.drawLine(line2);
    }

    QFont font = painter.font();
    font.setPixelSize(this->height);
    painter.setFont(font);

    pen.setColor({0,0,0});
    painter.setPen(pen);
    painter.drawText(QRect(0, 0, this->width, this->height), Qt::AlignCenter, "M");

    painter.end();


    QIcon::addPixmap(pix);
}
