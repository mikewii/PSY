#pragma once
#include <QString>
#include "Kana.hpp"

class Word;
class PhoneticsGenerator
{
public:
    QString makePhonetics( Word& _word, const SymbolEnum _selected ) const;
};
