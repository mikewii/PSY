#include "CPhonetics.hpp"
#include "CWord.hpp"

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


QString PhoneticsGenerator::makePhonetics( Word& _word, const SymbolEnum _selected ) const
{
    if ( _selected == Hiragana || _selected == Katakana )
        return "Wrong phonetics!";


    QString         out;
    auto&           word    = _word.getSymWord();
    auto            s       = _word.getSettings();
    const QString&  sym_i   = Column1.at(1).text.at(Hiragana);


    for ( u32 i = 0; i < word.size(); i++ )
    {
        auto& curSym = word.at(i);


        if ( curSym.phonetics == Phonetics::V )
        {
            // if there is symbol behind
            if ( i != 0 )
            {
                const Symbol&   prevSym = word.at(i - 1);
                const QChar&    prevCh  = out.at(i - 1);
                auto            toAdd   = curSym.text.at(_selected);

                // if using double vowel sign
                if ( s.useDoubleVowelSign )
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
                // if using oi
                if ( s.useoi )
                {
                    // if previous sym is CV
                    if ( prevSym.phonetics == Phonetics::CV )
                    {
                        // if current sym is i and previous is consonant with o
                        if ( curSym.text.at(Hiragana) == sym_i && _word.isGoodForOI(prevSym) )
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

        else if ( curSym.phonetics == Phonetics::N )
        {
            out += curSym.text.at(_selected);
        }

        // if its smallTsu and not at the end of word
        else if ( curSym.phonetics == Phonetics::SmallTSU && i + 1 < word.size() )
        {
            QString smallTsu;

            smallTsu = word.at(i + 1).text.at(_selected);
            smallTsu.truncate(smallTsu.size() - 1);

            out += smallTsu;
        }
    }

    return out;
}
