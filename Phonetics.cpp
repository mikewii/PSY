#include "Japanese.hpp"

QString Japanese::makePhonetics( SymbolEnum _phonetics )
{
    if ( _phonetics == Hiragana || _phonetics == Katakana )
        return "Wrong phonetics!";


    QString         out;
    auto&           word    = this->__word;
    auto&           f       = this->__flags;
    const QString&  sym_o   = Column1.at(4).text.at(Hiragana);
    const QString&  sym_i   = Column1.at(1).text.at(Hiragana);
    bool            skip    = false;


    for ( u32 i = 0; i < word.size(); i++ )
    {
        auto& sym = word.at(i);


        if ( skip )
        {
            skip = false;
            continue;
        }

        if ( sym.phonetics == Phonetics::V )
        {
            // if double sym in word bounds
            if ( i + 1 < word.size() )
            {
                // if using double vowel sign
                if ( f.useDoubleVowelSign )
                {
                    // if next sym if vowel
                    if ( sym.phonetics == word.at(i + 1).phonetics )
                    {
                        // if double and vowel sign
                        if ( sym.text.at(Hiragana) == word.at(i + 1).text.at(Hiragana) )
                        {
                            out += sym.text.at(_phonetics);

                            // to prevent confusing oo and oi
                            if ( sym.text.at(Hiragana) == sym_o )
                                out += sym.text.at(_phonetics);
                            else out += DoubleVowelSign;

                            skip = true;
                            continue;
                        }
                    }
                }
                // if using oi and sym is o
                if ( f.useoi && sym.text.at(Hiragana) == sym_o)
                {
                    // if next sym if vowel
                    if ( sym.phonetics == word.at(i + 1).phonetics )
                    {
                        // if next is i
                        if ( word.at(i + 1).text.at(Hiragana) == sym_i)
                        {
                            out += sym.text.at(_phonetics);
                            out += DoubleVowelSign;
                            skip = true;
                            continue;
                        }
                    }
                }
                out += sym.text.at(_phonetics);
                continue;
            }
            out += sym.text.at(_phonetics);
            continue;
        }

        if ( sym.phonetics == Phonetics::CV )
        {
            out += sym.text.at(_phonetics);
            continue;
        }

        if ( sym.phonetics == Phonetics::N )
        {
            out += sym.text.at(_phonetics);
            continue;
        }

        // if its smallTsu and not at the end of word
        if ( sym.phonetics == Phonetics::SmallTSU && i != word.size() - 1 )
        {
            QString smallTsu;

            smallTsu = word.at(i + 1).text.at(_phonetics);
            smallTsu.truncate(smallTsu.size() - 1);

            out += smallTsu;
        }
    }

    return out;
}
