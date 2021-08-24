#include "Japanese.hpp"

bool isGoodForOI( Symbol& _list )
{
    if ( _list.text.at(Hiragana) == Column2_K.at(4).text.at(Hiragana)) return true;
    if ( _list.text.at(Hiragana) == Column2_G.at(4).text.at(Hiragana)) return true;
    if ( _list.text.at(Hiragana) == Column3_S.at(4).text.at(Hiragana)) return true;
    if ( _list.text.at(Hiragana) == Column3_Z.at(4).text.at(Hiragana)) return true;
    if ( _list.text.at(Hiragana) == Column4_T.at(4).text.at(Hiragana)) return true;
    if ( _list.text.at(Hiragana) == Column4_D.at(4).text.at(Hiragana)) return true;
    if ( _list.text.at(Hiragana) == Column5_N.at(4).text.at(Hiragana)) return true;
    if ( _list.text.at(Hiragana) == Column6_H.at(4).text.at(Hiragana)) return true;
    if ( _list.text.at(Hiragana) == Column6_B.at(4).text.at(Hiragana)) return true;
    if ( _list.text.at(Hiragana) == Column6_P.at(4).text.at(Hiragana)) return true;

    return false;
}

QString Japanese::makePhonetics( SymbolEnum _phonetics )
{
    if ( _phonetics == Hiragana || _phonetics == Katakana )
        return "Wrong phonetics!";


    QString         out;
    auto&           word    = this->__word;
    auto&           f       = this->__flags;
    const QString&  sym_o   = Column1.at(4).text.at(Hiragana);
    const QString&  sym_i   = Column1.at(1).text.at(Hiragana);


    for ( u32 i = 0; i < word.size(); i++ )
    {
        auto& currentSym = word.at(i);


        if ( currentSym.phonetics == Phonetics::V )
        {
            // if there is symbol behind
            if ( i != 0 )
            {
                Symbol&         previousSym = word.at(i - 1);
                const QChar&    previousCh  = out.at(i - 1);

                // if using double vowel sign
                if ( f.useDoubleVowelSign )
                {
                    // if both sym vowel
                    if ( currentSym.phonetics == previousSym.phonetics )
                    {
                        // if both sym same
                        if ( currentSym.text.at(Hiragana) == previousSym.text.at(Hiragana) )
                        {
                            // if previous str isnt double vowel sign
                            if ( previousCh != DoubleVowelSign )
                            {
                                out += DoubleVowelSign;
                                continue;
                            }
                        }
                    }
                }
                // if using oi
                if ( f.useoi )
                {
                    // if previous sym is CV
                    if ( previousSym.phonetics == Phonetics::CV )
                    {
                        // if current sym is i and previous is consonant with o
                        if ( currentSym.text.at(Hiragana) == sym_i && isGoodForOI(previousSym) )
                        {
                            out += DoubleVowelSign;
                            continue;
                        }
                    }
                }
                out += currentSym.text.at(_phonetics);
                continue;
            }
            out += currentSym.text.at(_phonetics);
            continue;
        }

        else if ( currentSym.phonetics == Phonetics::CV )
        {
            out += currentSym.text.at(_phonetics);
        }

        else if ( currentSym.phonetics == Phonetics::N )
        {
            out += currentSym.text.at(_phonetics);
        }

        // if its smallTsu and not at the end of word
        else if ( currentSym.phonetics == Phonetics::SmallTSU && i != word.size() - 1 )
        {
            QString smallTsu;

            smallTsu = word.at(i + 1).text.at(_phonetics);
            smallTsu.truncate(smallTsu.size() - 1);

            out += smallTsu;
        }
    }

    return out;
}
