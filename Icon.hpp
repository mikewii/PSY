#pragma once
#include <QIcon>


class Icon : public QIcon
{
public:
    Icon();
    Icon( int _w, int _h );

private:
    std::vector<std::tuple<QRect,QRect,QColor,QColor>> lines;

    int width       = 128;
    int height      = 128;

    void    generate( void );
    void    generateLines( void );
    void    drawLines( void );

    QColor  getColor( void ) const;
};
