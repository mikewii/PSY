#pragma once
#include <QIcon>

class Icon : public QIcon
{
public:
    Icon();

    void generate( void );

private:
    int width   = 128;
    int height  = 128;
};
