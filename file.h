#pragma once
#include <QFile>
#include <QString>
#include "Emotion.hpp"


class CFile
{
public:
    CFile();
    ~CFile();

    void append( const QString _text, std::vector<std::pair<EmoEnum, int>> _emoVec );

private:
    QFile       file;

    void open( void );
    void close( void );
    void writeEmotion( const QStringList& _list, QFile& _file, int _id );

};
