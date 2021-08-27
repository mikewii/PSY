#include "CJapanese.hpp"
#include <random>
#include <time.h>
#include "CUtils.h"

void Japanese::generate( const Settings_s _settings )
{
    QString hiragana, katakana, phonetics_eng, phonetics_rus;


    this->__strings.clear();

    Word::setSettings(_settings);
    Word::makeSymList();

    /* generator */ Word::generateSymWord();
    /* generator */
    /* generator */ Grammar::grammarNN(Word::getWord());
    /* generator */ Grammar::grammarSmallTsu(Word::getWord());
    /* generator */ Grammar::grammarRemoveTriplets(Word::getWord());


    for ( auto& sym : Word::getSymWord() )
    {
        hiragana += sym.text.at(Hiragana);
        katakana += sym.text.at(Katakana);
    }

    phonetics_eng = PhoneticsGenerator::makePhonetics(Word::getWord(), PhoneticsENG);
    phonetics_rus = PhoneticsGenerator::makePhonetics(Word::getWord(), PhoneticsRUS);

    this->__strings.push_back(hiragana);
    this->__strings.push_back(katakana);
    this->__strings.push_back(phonetics_eng);
    this->__strings.push_back(phonetics_rus);
}

QString Japanese::check(const QString &_in, const SymbolEnum _selected)
{
    return Check::check(Word::getWord(), _in, _selected);
}

QString Japanese::getString( SymbolEnum _selected ) const
{
    if ( this->__strings.size() <= _selected ) return "getString() error!";
    else return this->__strings.at(_selected);
}
