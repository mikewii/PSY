#include "Icon.hpp"
#include <QPainter>
#include "Utils.h"

Icon::Icon()
{
    Icon::generate();
}

Icon::Icon( int _w, int _h ) : width(_w), height(_h)
{
    Icon::generate();
}

void Icon::generate()
{
    Icon::generateLines();
    Icon::drawLines();
}

void Icon::generateLines()
{
    auto    filled  = 0;
    auto    limit   = Icon::height - 1;


    for(;filled < limit;)
    {
        auto height = Utils::getRandom(1, limit - filled);
        auto hSplit = Utils::getRandom(1, limit);
        auto col1   = Icon::getColor();
        auto col2   = Icon::getColor();


        QRect line1(0, filled, hSplit, height + 1);
        QRect line2(hSplit, filled, Icon::width - hSplit, height + 1);

        filled += height;

        Icon::lines.push_back({line1, line2, col1, col2});
    }
}

void Icon::drawLines( void )
{
    QPixmap     pix(this->width, this->height);
    QPainter    painter;


    painter.begin(&pix);

    for ( auto& line : Icon::lines )
    {
        auto& rect1 = std::get<0>(line);
        auto& rect2 = std::get<1>(line);
        auto& col1  = std::get<2>(line);
        auto& col2  = std::get<3>(line);


        painter.fillRect(rect1, col1);
        painter.fillRect(rect2, col2);
    }

    painter.end();


    Icon::addPixmap(pix);
}

QColor Icon::getColor( void ) const
{
    int r = Utils::getRandom(30, 200);
    int g = Utils::getRandom(70, 200);
    int b = Utils::getRandom(70, 200);

    return {r,g,b};
}
