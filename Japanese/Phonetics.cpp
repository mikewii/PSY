#include "Japanese/Phonetics.hpp"


uint32_t findIndex( const Symbol& _sym, const SymbolEnum _selected = Hiragana )
{
    const std::vector<const SymVec*> columnsVec =
    {
        &Column1,
        &Column2_K,
        &Column2_G,
        &Column3_S,
        &Column3_Z,
        &Column4_T,
        &Column4_D,
        &Column5_N,
        &Column6_H,
        &Column6_B,
        &Column6_P
    };

    uint32_t    index   = 0;
    bool        done    = false;


    for ( const auto& col : columnsVec )
    {
        for ( uint32_t i = 0; i < col->size(); i++ )
        {
            if ( _sym.text.at(_selected) == col->at(i).text.at(_selected) )
            {
                index   = i;
                done    = true;
                break;
            }
        }
        if ( done ) break;
    }

    return index;
}


QString PhoneticsGenerator::makePhonetics( const SymbolEnum _selected )
{
    if ( _selected == Hiragana || _selected == Katakana )
        return "Wrong phonetics!";


    QString         out;
    const QString&  sym_u   = Column1.at(2).text.at(Hiragana);


    for ( u32 i = 0; i < Word::symWord.size(); i++ )
    {
        auto& curSym = Word::symWord.at(i);


        if ( curSym.phonetics == Phonetics::V )
        {
            // if there is symbol behind
            if ( i != 0 )
            {
                const Symbol&   prevSym = Word::symWord.at(i - 1);
                const QChar&    prevCh  = out.at(i - 1);
                auto            toAdd   = curSym.text.at(_selected);

                // if using double vowel sign
                if ( Word::settings.useDoubleVowelSign )
                {
                    // if both sym vowel
                    if ( curSym.phonetics == prevSym.phonetics && prevCh != DoubleVowelSign )
                    {
                        // if both sym same
                        if ( curSym.text.at(Hiragana) == prevSym.text.at(Hiragana) )
                            toAdd = DoubleVowelSign;
                    }
                    // if previous is consonant
                    else if ( prevSym.phonetics == Phonetics::CV )
                    {
                        // find out both sym index
                        if ( findIndex(curSym) == findIndex(prevSym) )
                            toAdd = DoubleVowelSign;
                    }
                }
                // if using ou
                if ( Word::settings.useou )
                {
                    // if previous sym is CV
                    if ( prevSym.phonetics == Phonetics::CV )
                    {
                        // if current sym is u and previous is consonant with o
                        if ( curSym.text.at(Hiragana) == sym_u && Word::isGoodForOU(prevSym) )
                            toAdd = DoubleVowelSign;
                    }
                }

                out += toAdd;
            }
            else out += curSym.text.at(_selected);
        }

        else if ( curSym.phonetics == Phonetics::CV )
        {
            out += curSym.text.at(_selected);
        }

        else if ( curSym.phonetics == Phonetics::D )
        {
            out += curSym.text.at(_selected);
        }

        else if ( curSym.phonetics == Phonetics::CVD )
        {
            out += curSym.text.at(_selected);
        }

        else if ( curSym.phonetics == Phonetics::N )
        {
            out += curSym.text.at(_selected);
        }

        // if its smallTsu and not at the end of word
        else if ( curSym.phonetics == Phonetics::SmallTSU && i + 1 < Word::symWord.size() )
        {
            QString smallTsu;

            smallTsu = Word::symWord.at(i + 1).text.at(_selected);
            smallTsu.truncate(smallTsu.size() - 1);

            out += smallTsu;
        }
    }

    return out;
}
