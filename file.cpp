#include "file.h"
#include <QTime>
#include <QDir>

CFile::CFile()
{
    this->open();
}

CFile::~CFile()
{
    this->close();
}


void CFile::writeEmotion( const QStringList& _list, QFile& _file, int _id )
{
    const char  space   = ' ';


    auto    selection  = _list.at(_id);
    auto    text       = selection.toUtf8();
    auto    size       = text.size();
    _file.write(text, size);
    _file.write(&space, sizeof(space));
}

void CFile::append( const QString _text, std::vector<std::pair<EmoEnum, int>> _emoVec )
{
    if ( !this->file.isOpen() )
        return;


    QTime       time    = QTime::currentTime();
    QDate       date    = QDate::currentDate();
    auto        fmt     = Qt::DateFormat::SystemLocaleDate;
    const char  space   = ' ';
    const char  divider = '|';
    const char  nl      = '\n';

    /* date time | emotion
     * text
     *
     */


    // date
    auto    dateText = date.toString(fmt).toUtf8();
    auto    dateSize = dateText.size();
    this->file.write(dateText, dateSize);
    this->file.write(&space, sizeof(space));


    // time
    auto    timeText = time.toString(fmt).toUtf8();
    auto    timeSize = timeText.size();
    this->file.write(timeText, timeSize);
    this->file.write(&space, sizeof(space));
    this->file.write(&divider, sizeof(divider));
    this->file.write(&space, sizeof(space));


    // emotion
    for ( auto& emo : _emoVec )
    {
        if ( emo.second != 0 )
        {
            switch(emo.first)
            {
            case EmoEnum::anger:
            {
                this->writeEmotion(EmoAnger, this->file, emo.second);
                break;
            }
            case EmoEnum::fear:
            {
                this->writeEmotion(EmoFear, this->file, emo.second);
                break;
            }
            case EmoEnum::sadness:
            {
                this->writeEmotion(EmoSadness, this->file, emo.second);
                break;
            }
            case EmoEnum::joy:
            {
                this->writeEmotion(EmoJoy, this->file, emo.second);
                break;
            }
            case EmoEnum::love:
            {
                this->writeEmotion(EmoLove, this->file, emo.second);
                break;
            }
            default:break;
            };
        }
    }
    this->file.write(&nl, sizeof(nl));


    // text
    auto    text = _text.toUtf8();
    auto    size = text.size();
    this->file.write(text, size);
    this->file.write(&nl, sizeof(nl));
    this->file.write(&nl, sizeof(nl));
}

void CFile::open()
{
    QDir        dir;


    this->file.setFileName(dir.relativeFilePath("journal.txt"));
    this->file.open(QFile::ReadWrite | QFile::Append);
}

void CFile::close()
{
    if ( this->file.isOpen() )
        this->file.close();
}
