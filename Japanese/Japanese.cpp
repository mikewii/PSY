#include "Japanese/Japanese.hpp"
#include "Utils.h"

void Japanese::generate( const Settings_s _settings )
{
    Word::run(_settings);
    Grammar::run();
    PhoneticsGenerator::run();
}

QString Japanese::check( const QString &_in, const SymbolEnum _selected ) const
{
    return Check::check(_in, _selected);
}

QString Japanese::getString( const SymbolEnum _selected ) const
{
    if ( Word::strings.size() <= _selected ) return "";
    else return Word::strings.at(_selected);
}
