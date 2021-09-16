#include "Journal.hpp"
#include <QDir>
#include <QTime>

#ifdef __linux__
    const char* eol = "\n";
#elif _WIN32
    const char* eol = "\r\n";
#endif


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


    // date time
    fulltext += date.toString(Journal::fmt);
    fulltext += space;
    fulltext += time.toString(Journal::fmt);
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

    fulltext += eol;


    // text
    fulltext += ":> ";
    fulltext += _text;
    fulltext += eol;
    fulltext += eol;


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
