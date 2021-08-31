#pragma once
#include "Japanese/Word.hpp"


class Check : virtual public Word
{
public:
    QString check( const QString& _in, const SymbolEnum _selected ) const;
    bool    alphabetCheck( const QString& _text, const SymbolEnum _selected) const;

private:
    QString pushSymbol( const QString& _symbol, const QString& _wordSym ) const;
};
