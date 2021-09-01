#pragma once
#include <stdint.h>
#include <QByteArray>

class Utils
{
public:
    static void         initRandom( void );
    static uint32_t     getRandom( uint32_t _min, uint32_t _max );
    static bool         getRandomBool( void );

    static QByteArray*  getAppIconBytesArray( void );
    static QByteArray*  getBytesArray( bool _erase = false );
};
