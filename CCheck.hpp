#pragma once
#include "Kana.hpp"


class Word;
class Check
{
public:
    QString check( Word& _word, const QString& _in, const SymbolEnum _selected ) const;
    bool    alphabetCheck( const QString& _text, const SymbolEnum _selected) const;
};
