#include "Utils.h"
#include <chrono>
#include <random>

static std::mt19937 rng;

static QByteArray   curSvg;
static QByteArray   appSvg;

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

uint32_t    Utils::getRandomChance( const std::vector<uint32_t>& _vec )
{
    std::discrete_distribution<uint32_t>    uniform(_vec.begin(), _vec.end());

    return (uniform(rng));
}


bool    Utils::getRandomBool( void )
{
    return Utils::getRandom(0, 1);
}

QByteArray* Utils::getAppIconBytesArray( void )
{
    return &appSvg;
}


QByteArray* Utils::getBytesArray( bool _erase )
{
    if ( _erase )
        curSvg.clear();

    return &curSvg;
}
