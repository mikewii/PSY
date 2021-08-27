#include "CJapanese.hpp"
#include <random>
#include <time.h>
#include "CUtils.h"

void Japanese::generate( const Settings_s _settings )
{
    QString hiragana, katakana, phonetics_eng, phonetics_rus;


    Word::prepare(_settings);

    /* generator */ Word::generateSymWord();
    /* generator */
    /* generator */ Grammar::grammarNN();
    /* generator */ Grammar::grammarSmallTsu();
    /* generator */ Grammar::grammarRemoveTriplets();

    for ( auto& sym : Word::getSymWord() )
    {
        hiragana += sym.text.at(Hiragana);
        katakana += sym.text.at(Katakana);
    }

    phonetics_eng = PhoneticsGenerator::makePhonetics(PhoneticsENG);
    phonetics_rus = PhoneticsGenerator::makePhonetics(PhoneticsRUS);

    Japanese::getStringList() = QStringList{hiragana, katakana, phonetics_eng, phonetics_rus};
}

QString Japanese::check( const QString &_in, const SymbolEnum _selected )
{
    return Check::check(_in, _selected);
}

QString Japanese::getString( const SymbolEnum _selected ) const
{
    if ( this->__strings.size() <= _selected ) return "";
    else return this->__strings.at(_selected);
}
