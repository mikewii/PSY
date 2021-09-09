#pragma once
#include <stdint.h>
#include <QByteArray>
#include <vector>

class Utils
{
public:
    static void         initRandom( void );
    static uint32_t     getRandom( uint32_t _min, uint32_t _max );
    static uint32_t     getRandomChance( const std::vector<uint32_t>& _vec );

    static bool         getRandomBool( void );

    static QByteArray*  getAppIconBytesArray( void );
    static QByteArray*  getBytesArray( bool _erase = false );
};
