#include "file.h"
#include <QDir>

CFile::CFile()
{}

CFile::~CFile()
{}

/* date time | emotion
 * text
 *
 */
bool CFile::append( const QString& _text, int _emoAnger, int _emoFear, int _emoSadness, int _emoJoy, int _emoLove )
{
    this->open();

    if ( !this->file.isOpen() )
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
    if ( _emoAnger != 0 )
    {
        fulltext += space;
        fulltext += EmoAnger.at(_emoAnger);
    }
    if ( _emoFear != 0 )
    {
        fulltext += space;
        fulltext += EmoFear.at(_emoFear);
    }
    if ( _emoSadness != 0 )
    {
        fulltext += space;
        fulltext += EmoSadness.at(_emoSadness);
    }
    if ( _emoJoy != 0 )
    {
        fulltext += space;
        fulltext += EmoJoy.at(_emoJoy);
    }
    if ( _emoLove != 0 )
    {
        fulltext += space;
        fulltext += EmoLove.at(_emoLove);
    }

    fulltext += nl;


    // text
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

void CFile::open( void )
{
    QDir        dir;


    this->file.setFileName(dir.relativeFilePath("journal.txt"));
    this->file.open(QFile::ReadWrite | QFile::Append);
}

void CFile::close( void )
{
    if ( this->file.isOpen() )
        this->file.close();
}
