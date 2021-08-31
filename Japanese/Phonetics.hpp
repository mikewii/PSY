#pragma once
#include <QString>
#include "Japanese/Word.hpp"

class PhoneticsGenerator : virtual public Word
{
public:
    void run( void );

    QString makePhonetics( const SymbolEnum _selected );
};
