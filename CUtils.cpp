#include "CUtils.h"

std::mt19937 Utils::rng;

void Utils::initRandom()
{
    rng.seed(time(NULL));
}

uint32_t Utils::getRandom( uint32_t _min, uint32_t _max )
{
    if ( _max == 0 )
        _max = UINT32_MAX;
    std::uniform_int_distribution<uint32_t>  uniform(_min, _max);

    return (uniform(rng));
}
