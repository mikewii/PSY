#include "Icon.hpp"
#include <QPainter>
#include "Utils.h"

Icon::Icon( bool _text ) : useText(_text)
{
    Icon::generate();
}

Icon::Icon( int _w, int _h, bool _text ) : width(_w), height(_h), useText(_text)
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
    QPixmap         pix(this->width, this->height);
    QPainter        painter;



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

    if ( Icon::useText )
        Icon::drawText(painter);

    painter.end();


    Icon::addPixmap(pix);
}

void Icon::drawText( QPainter& _painter )
{
    const QString   mike    = "ミ\nケ";
    const QString   wii     = "ヰ\nイ";

    auto    textSize    = Icon::height / 3;
    QFont   font        = _painter.font();
    QPen    pen({0, 0, 0});

    // get halfs
    QRect leftHalf  (0, 0, Icon::width / 2, Icon::height);
    QRect rightHalf (Icon::width / 2, 0, Icon::width / 2, Icon::height);

    // get bg
    auto xPaddingFull = Icon::width / 2 - textSize;
    auto yPaddingFull = Icon::height / 2 - textSize;

    QRect leftBg    (xPaddingFull / 2, yPaddingFull / 2, Icon::width / 2 - xPaddingFull, Icon::height - yPaddingFull);
    QRect rightBg   (Icon::width / 2 + xPaddingFull / 2, yPaddingFull / 2, Icon::width / 2 - xPaddingFull, Icon::height - yPaddingFull);



    font.setPixelSize(textSize);
    _painter.setFont(font);

    _painter.fillRect(leftBg, Icon::getColor(true));
    _painter.fillRect(rightBg, Icon::getColor(true));

    _painter.setPen(pen);
    _painter.drawText(rightHalf, Qt::AlignCenter, mike);
    _painter.drawText(leftHalf, Qt::AlignCenter, wii);
}

QColor Icon::getColor( bool _grey ) const
{
    int r = Utils::getRandom(70, 200);
    int g = Utils::getRandom(70, 200);
    int b = Utils::getRandom(70, 200);

    if ( _grey )
        return {r,r,r};

    return {r,g,b};
}
