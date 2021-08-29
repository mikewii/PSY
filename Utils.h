#pragma once
#include <stdint.h>

class Utils
{
public:
    static void         initRandom( void );
    static uint32_t     getRandom( uint32_t _min, uint32_t _max );
    static bool         getRandomBool( void );
};
