#include "CJapanese.hpp"

void Japanese::grammarSmallTsu( void )
{
    if ( !Japanese::__settings.longConsonant || !this->__settings.multipleColumn )
        return;

    auto&   word = this->__word;


    for ( u32 i = 0; i < word.size(); i++ )
    {
        auto& sym = word.at(i);

        // cant be first
        if ( sym.phonetics == LongConsonant.phonetics && i == 0 )
            word.at(i) = this->getRandomSym(Phonetics(V | CV));

        // cant be last // not
        if ( sym.phonetics == LongConsonant.phonetics && i == word.size() - 1 )
        {
            auto phonetics = this->__settings.nn ? Phonetics(V | CV | N) : Phonetics(V | CV);

            word.at(i) = this->getRandomSym(phonetics);
        }

        // next sym can be only CV
        if (  sym.phonetics == LongConsonant.phonetics && i != 0 && i + 1 < word.size() )
        {
            if ( word.at(i + 1).phonetics != Phonetics::CV )
            {
                word.at(i + 1) = this->getRandomSym(Phonetics(CV));
            }
        }
    }
}

void Japanese::grammarNN( void )
{
    if ( !this->__settings.nn )
        return;

    Phonetics   phonetics = Phonetics::V;
    u32         last = this->__word.size() - 1;


    if ( this->__settings.longConsonant )
        phonetics = static_cast<Phonetics>( phonetics | Phonetics::SmallTSU );
    if ( this->__settings.multipleColumn )
        phonetics = static_cast<Phonetics>( phonetics | Phonetics::CV );


    for ( u32 i = 0; i < this->__word.size(); i ++ )
    {
        auto& sym = this->__word.at(i);

        if ( sym.phonetics == NN.phonetics && i != last )
            sym = this->getRandomSym(phonetics);
    }
}

void Japanese::grammarRemoveTriplets( void )
{
    auto inGeneratorLimit   = this->__settings.wordLength / 2 <= this->__symList->size() + 2;
    auto acceptableWordSize = this->__settings.wordLength >= 3;
    if ( !this->__settings.preventTriplets || !inGeneratorLimit || !acceptableWordSize )
        return;

    Symbol  s;
    auto&   word = this->__word;


    for ( u32 i = 0; i < word.size(); i++ )
    {
        auto&   sym = word.at(i);


        if ( i + 2 < word.size() )
        {
            // if we found double
            if ( sym.text.at(Hiragana) == word.at(i + 1).text.at(Hiragana) )
            {
                // if we found triplet
                if ( sym.text.at(Hiragana) == word.at(i + 2).text.at(Hiragana) )
                {
                    for(;;)
                    {
                        s = this->getRandomSym(Phonetics(V | CV));

                        if ( sym.text.at(Hiragana) != s.text.at(Hiragana) ) break;
                    }

                    word.at(i + 2) = s;
                }
            }
        }
    }
}
