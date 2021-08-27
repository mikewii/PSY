#pragma once
#include <QString>
#include "CWord.hpp"

class PhoneticsGenerator : virtual public Word
{
public:
    QString makePhonetics( const SymbolEnum _selected );
};
