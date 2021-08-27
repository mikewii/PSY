#pragma once
#include <random>

class Utils
{
public:
    static void        initRandom( void );
    static uint32_t    getRandom( uint32_t _min, uint32_t _max );

private:
    static std::mt19937 rng;
};
