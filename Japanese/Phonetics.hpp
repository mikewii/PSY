#pragma once
#include <QString>
#include "Japanese/Word.hpp"

class PhoneticsGenerator : virtual public Word
{
public:
    QString makePhonetics( const SymbolEnum _selected );
};
