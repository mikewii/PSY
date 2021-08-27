#pragma once
#include "Japanese/Word.hpp"


class Check : virtual public Word
{
public:
    QString check( const QString& _in, const SymbolEnum _selected );
    bool    alphabetCheck( const QString& _text, const SymbolEnum _selected) const;
};
