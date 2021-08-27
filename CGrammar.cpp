#include "CGrammar.hpp"
#include "CWord.hpp"

void Grammar::grammarSmallTsu( Word& _word )
{
    auto    settings    = _word.getSettings();
    auto&   word        = _word.getSymWord();


    if ( !settings.longConsonant || !settings.multipleColumn )
        return;


    for ( u32 i = 0; i < word.size(); i++ )
    {
        auto& sym = word.at(i);

        // cant be first
        if ( sym.phonetics == LongConsonant.phonetics && i == 0 )
            word.at(i) = _word.getRandomSym(Phonetics(V | CV));

        // cant be last // not
        if ( sym.phonetics == LongConsonant.phonetics && i == word.size() - 1 )
        {
            auto phonetics = settings.nn ? Phonetics(V | CV | N) : Phonetics(V | CV);

            word.at(i) = _word.getRandomSym(phonetics);
        }

        // next sym can be only CV
        if (  sym.phonetics == LongConsonant.phonetics && i != 0 && i + 1 < word.size() )
        {
            if ( word.at(i + 1).phonetics != Phonetics::CV )
            {
                word.at(i + 1) = _word.getRandomSym(Phonetics(CV));
            }
        }
    }
}

void Grammar::grammarNN( Word& _word )
{
    auto    settings    = _word.getSettings();
    auto&   word        = _word.getSymWord();


    if ( !settings.nn )
        return;


    Phonetics   phonetics = Phonetics::V;
    u32         last = word.size() - 1;


    if ( settings.longConsonant )
        phonetics = static_cast<Phonetics>( phonetics | Phonetics::SmallTSU );
    if ( settings.multipleColumn )
        phonetics = static_cast<Phonetics>( phonetics | Phonetics::CV );


    for ( u32 i = 0; i < word.size(); i ++ )
    {
        auto& sym = word.at(i);

        if ( sym.phonetics == NN.phonetics && i != last )
            sym = _word.getRandomSym(phonetics);
    }
}

void Grammar::grammarRemoveTriplets( Word& _word )
{
    auto    settings   = _word.getSettings();
    auto&   word      = _word.getSymWord();
    auto&   symList   = _word.getSymList();
    Symbol  s;


    auto inGeneratorLimit   = settings.wordLength / 2 <= symList.size() + 2;
    auto acceptableWordSize = settings.wordLength >= 3;
    if ( !settings.preventTriplets || !inGeneratorLimit || !acceptableWordSize )
        return;




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
                        s = _word.getRandomSym(Phonetics(V | CV));

                        if ( sym.text.at(Hiragana) != s.text.at(Hiragana) ) break;
                    }

                    word.at(i + 2) = s;
                }
            }
        }
    }
}
