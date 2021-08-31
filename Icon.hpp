#pragma once
#include <QIcon>


class Icon : public QIcon
{
public:
    Icon( bool _text = false );
    Icon( int _w, int _h, bool _text = false );

private:
    std::vector<std::tuple<QRect,QRect,QColor,QColor>> lines;

    int     width   = 128;
    int     height  = 128;
    bool    useText = false;
    bool    rotated = false;

    void    generate( void );
    void    generateLines( void );
    void    drawLines( void );
    void    drawLinesDo( QPainter& _painter );
    void    drawText( QPainter& _painter );

    QColor  getColor( bool _grey = false ) const;
};
