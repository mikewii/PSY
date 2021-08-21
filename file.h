#pragma once
#include <QFile>
#include <QString>
#include <QTime>
#include "Emotion.hpp"

/* date time | emotion
 * text
 *
 */

class CFile
{
public:
    static const auto   fmt     = Qt::DateFormat::SystemLocaleDate;
    static const char   space   = ' ';
    static const char   divider = '|';
    static const char   nl      = '\n';


    CFile();

    bool append( const QString& _text, int _emoAnger, int _emoFear, int _emoSadness, int _emoJoy, int _emoLove );

private:
    QFile       file;

    bool open( void );
    void close( void );

};
