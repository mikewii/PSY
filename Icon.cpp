#include "Icon.hpp"
#include "Utils.h"
#include <QPainter>
#include <QtSvg/QSvgGenerator>
#include <QBuffer>


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
    Icon::rotated = Utils::getRandomBool();

    Icon::generateLines();
    Icon::drawLines();
}

void Icon::generateLines()
{
    auto    filled  = 0;
    auto    limit   = Icon::height - 1;
    auto    heightLimit = Icon::rotated ? 4 : 2;
    auto    widthLimit  = Icon::rotated ? Icon::width / 4 : limit;


    for(;filled < limit;)
    {
        int     height = Utils::getRandom(1, limit - filled);
        int     hSplit = Utils::getRandom(1, widthLimit);
        auto    col1   = Icon::getColor();
        auto    col2   = Icon::getColor();

        if ( height > Icon::height / heightLimit ) continue;

        QRect line1(0, filled, hSplit, height + 1);
        QRect line2(hSplit, filled, Icon::width - hSplit, height + 1);

        filled += height;

        Icon::lines.push_back({line1, line2, col1, col2});
    }
}


void Icon::drawLines( void )
{
    // to fix: very first icon is lost on new generation

    QBuffer         buffer(&Utils::getBytesArray(true));
    QPixmap         pix;
    QSvgGenerator   svg;
    QPainter        painter;


    svg.setSize(QSize(Icon::width, Icon::height));
    svg.setViewBox(QRect(0, 0, Icon::width, Icon::height));
    svg.setTitle("PSY Icon");
    svg.setDescription("An SVG drawing created by the SVG Generator");
    svg.setOutputDevice(&buffer);


    painter.begin(&svg);

    painter.fillRect(QRect(0, 0, Icon::width, Icon::height), Icon::getColor());

    if ( Icon::rotated )
    {
        for ( auto i = 0; i < 4; i++ )
        {
            Icon::drawLinesDo(painter);

            painter.translate(Icon::width, 0);
            painter.rotate(90.f);
        }
    }
    else Icon::drawLinesDo(painter);


    if ( Icon::useText )
        Icon::drawText(painter);

    painter.end();


    pix.loadFromData(buffer.data(), "SVG");

    Icon::addPixmap(pix);
}

void Icon::drawLinesDo(QPainter &_painter)
{
    for ( auto& line : Icon::lines )
    {
        auto& rect1 = std::get<0>(line);
        auto& rect2 = std::get<1>(line);
        auto& col1  = std::get<2>(line);
        auto& col2  = std::get<3>(line);


        _painter.fillRect(rect1, col1);

        if ( !Icon::rotated )
            _painter.fillRect(rect2, col2);
    }
}

void Icon::drawText( QPainter& _painter )
{
    static const QString   mike    = "ミ\nケ";
    static const QString   wii     = "ヰ\nイ";


    bool    colored     = Utils::getRandomBool();
    bool    centered    = Utils::getRandomBool();
    auto    textSize    = Icon::height / 3;
    QFont   font        = _painter.font();
    QPen    pen({0, 0, 0});

    // get halfs
    QRect leftHalf  (0, 0, Icon::width / 2, Icon::height);
    QRect rightHalf (Icon::width / 2, 0, Icon::width / 2, Icon::height);

    // get bg
    auto xPaddingFull = Icon::width / 2 - textSize;
    auto yPaddingFull = Icon::height / 2 - textSize;

    QRect leftBg(
                xPaddingFull / 2,
                yPaddingFull / 2,
                Icon::width / 2 - xPaddingFull,
                Icon::height - yPaddingFull);

    QRect rightBg(
                Icon::width / 2 + xPaddingFull / 2,
                yPaddingFull / 2,
                Icon::width / 2 - xPaddingFull,
                Icon::height - yPaddingFull);


    font.setPixelSize(textSize);
    _painter.setFont(font);


    if ( centered )
    {
        QRect centerBg(
                    Icon::width / 2 - textSize - ( textSize / 16 ),
                    Icon::height / 2 - textSize - ( textSize / 8 ),
                    textSize * 2 + ( textSize / 8 ),
                    textSize * 2 + ( textSize / 4 ));

        _painter.fillRect(centerBg, Icon::getColor(colored));

        _painter.setPen(pen);
        _painter.drawText(rightHalf, Qt::AlignVCenter | Qt::AlignLeft, mike);
        _painter.drawText(leftHalf, Qt::AlignVCenter | Qt::AlignRight, wii);
    }
    else
    {
        _painter.fillRect(leftBg, Icon::getColor(colored));
        _painter.fillRect(rightBg, Icon::getColor(colored));

        _painter.setPen(pen);
        _painter.drawText(rightHalf, Qt::AlignCenter, mike);
        _painter.drawText(leftHalf, Qt::AlignCenter, wii);
    }
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
