#pragma once
#include <QFile>
#include <QString>
#include "Journal/Emotion.hpp"

/* date time | emotion
 * text
 *
 */

class Journal
{
public:
    static const char   space   = ' ';
    static const char   divider = '|';
    static const auto   fmt     = Qt::DateFormat::ISODate;

    struct Emotion {
        int Anger;
        int Fear;
        int Sadness;
        int Joy;
        int Love;
    };


    Journal();

    bool append( const QString& _text, const Emotion _emotion );

private:
    QFile       file;

    bool open( void );
    void close( void );

};
