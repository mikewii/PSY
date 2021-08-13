#pragma once
#include <QFile>
#include <QString>
#include <QTime>
#include "Emotion.hpp"


class CFile
{
public:
    static const auto   fmt     = Qt::DateFormat::SystemLocaleDate;
    static const char   space   = ' ';
    static const char   divider = '|';
    static const char   nl      = '\n';


    CFile();
    ~CFile();

    bool append( const QString& _text, int _emoAnger, int _emoFear, int _emoSadness, int _emoJoy, int _emoLove );

private:
    QFile       file;

    void open( void );
    void close( void );

};
