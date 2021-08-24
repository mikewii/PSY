#include "Japanese.hpp"

QString Japanese::makePhonetics( const SymbolEnum _selected ) const
{
    if ( _selected == Hiragana || _selected == Katakana )
        return "Wrong phonetics!";


    QString         out;
    auto&           word    = this->__word;
    auto&           f       = this->__flags;
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
                if ( f.useDoubleVowelSign )
                {
                    // if both sym vowel
                    if ( curSym.phonetics == prevSym.phonetics )
                    {
                        // if both sym same
                        if ( curSym.text.at(Hiragana) == prevSym.text.at(Hiragana) )
                        {
                            // if previous str isnt double vowel sign
                            if ( prevCh != DoubleVowelSign )
                                toAdd = DoubleVowelSign;
                        }
                    }
                }
                // if using oi
                if ( f.useoi )
                {
                    // if previous sym is CV
                    if ( prevSym.phonetics == Phonetics::CV )
                    {
                        // if current sym is i and previous is consonant with o
                        if ( curSym.text.at(Hiragana) == sym_i && this->isGoodForOI(prevSym) )
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
