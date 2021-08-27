#include "CGrammar.hpp"
#include "CWord.hpp"

void Grammar::grammarSmallTsu( void )
{
    if ( !Word::settings.longConsonant || !Word::settings.multipleColumn )
        return;


    for ( u32 i = 0; i < Word::symWord.size(); i++ )
    {
        auto& sym = Word::symWord.at(i);

        // cant be first
        if ( sym.phonetics == LongConsonant.phonetics && i == 0 )
            Word::symWord.at(i) = Word::getRandomSym({V,CV});

        // cant be last // not
        if ( sym.phonetics == LongConsonant.phonetics && i == Word::symWord.size() - 1 )
        {
            std::vector<Phonetics> phonetics = settings.nn ? std::vector<Phonetics>{V,CV,N} : std::vector<Phonetics>{V,CV};

            Word::symWord.at(i) = Word::getRandomSym(phonetics);
        }

        // next sym can be only CV
        if (  sym.phonetics == LongConsonant.phonetics && i != 0 && i + 1 < Word::symWord.size() )
        {
            if ( Word::symWord.at(i + 1).phonetics != Phonetics::CV )
            {
                Word::symWord.at(i + 1) = Word::getRandomSym({CV});
            }
        }
    }
}

void Grammar::grammarNN( void )
{
    if ( !Word::settings.nn )
        return;


    std::vector<Phonetics>  phonetics = {V};
    u32                     last = Word::symWord.size() - 1;


    if ( settings.longConsonant )
        phonetics.push_back(Phonetics::SmallTSU);
    if ( settings.multipleColumn )
        phonetics.push_back(Phonetics::CV);


    for ( u32 i = 0; i < Word::symWord.size(); i ++ )
    {
        auto& sym = Word::symWord.at(i);

        if ( sym.phonetics == NN.phonetics && i != last )
            sym = Word::getRandomSym(phonetics);
    }
}

void Grammar::grammarRemoveTriplets( void )
{
    Symbol  s;


    auto inGeneratorLimit   = Word::settings.wordLength / 2 <= Word::symList.size() + 2;
    auto acceptableWordSize = Word::settings.wordLength >= 3;
    if ( !Word::settings.preventTriplets || !inGeneratorLimit || !acceptableWordSize )
        return;


    for ( u32 i = 0; i < Word::symWord.size(); i++ )
    {
        auto&   sym = Word::symWord.at(i);


        if ( i + 2 < Word::symWord.size() )
        {
            // if we found double
            if ( sym.text.at(Hiragana) == Word::symWord.at(i + 1).text.at(Hiragana) )
            {
                // if we found triplet
                if ( sym.text.at(Hiragana) == Word::symWord.at(i + 2).text.at(Hiragana) )
                {
                    for(;;)
                    {
                        s = Word::getRandomSym({V,CV});

                        if ( sym.text.at(Hiragana) != s.text.at(Hiragana) ) break;
                    }

                    Word::symWord.at(i + 2) = s;
                }
            }
        }
    }
}
