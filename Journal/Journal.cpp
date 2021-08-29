#include "Journal.hpp"
#include <QDir>
#include <QTime>


Journal::Journal()
{
    this->file.setFileName(QDir::homePath() + QDir::separator() + "journal.txt");
}

bool Journal::append( const QString& _text, const Emotion _emotion )
{
    if ( !this->open() )
        return false;


    QString fulltext;
    auto    time    = QTime::currentTime();
    auto    date    = QDate::currentDate();
    auto    fmt     = Qt::DateFormat::SystemLocaleDate;


    // date time
    fulltext += date.toString(fmt);
    fulltext += space;
    fulltext += time.toString(fmt);
    fulltext += space;
    fulltext += divider;


    // emotion
    if ( _emotion.Anger != 0 )
    {
        fulltext += space;
        fulltext += EmoAnger.at(_emotion.Anger);
    }
    if ( _emotion.Fear != 0 )
    {
        fulltext += space;
        fulltext += EmoFear.at(_emotion.Fear);
    }
    if ( _emotion.Sadness != 0 )
    {
        fulltext += space;
        fulltext += EmoSadness.at(_emotion.Sadness);
    }
    if ( _emotion.Joy != 0 )
    {
        fulltext += space;
        fulltext += EmoJoy.at(_emotion.Joy);
    }
    if ( _emotion.Love != 0 )
    {
        fulltext += space;
        fulltext += EmoLove.at(_emotion.Love);
    }

    fulltext += nl;


    // text
    fulltext += ":> ";
    fulltext += _text;
    fulltext += nl;
    fulltext += nl;


    // write
    auto    text = fulltext.toUtf8();
    auto    size = text.size();
    this->file.write(text, size);

    this->close();

    return true;
}

bool Journal::open( void )
{
    return this->file.open(QFile::Append);
}

void Journal::close( void )
{
    if ( this->file.isOpen() )
        this->file.close();
}
