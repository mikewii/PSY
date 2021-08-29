#include "Utils.h"
#include <chrono>
#include <random>

static std::mt19937 rng;

void Utils::initRandom()
{
    //auto t = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto t = time(NULL);

    rng.seed(t);
}

uint32_t Utils::getRandom( uint32_t _min, uint32_t _max )
{
    if ( _max == 0 )
        _max = UINT32_MAX;
    std::uniform_int_distribution<uint32_t>  uniform(_min, _max);

    return (uniform(rng));
}
