#include "Japanese.hpp"


static const QString    green  = "<span style='color:#00cc00;'>";
static const QString    red    = "<span style='color:#cc0000;'>";
static const QString    close  = "</span>";


QString makeRedHTML( const QString& _str ) { return red + _str + close; }
QString makeGreenHTML( const QString& _str ) { return green + _str + close; }
QString pushSym( const QString& _symbol, const QString& _wordSym )
{
    if ( _symbol == _wordSym ) return makeGreenHTML(_symbol);
    else return makeRedHTML(_symbol);
}

QString Japanese::check( const QString& _in, const SymbolEnum _selected ) const
{    
    QString         out;
    const QString&  str         = this->getString(_selected);
    auto            isPhonetics = _selected == PhoneticsENG || _selected == PhoneticsRUS;
    auto&           word        = this->__word;   


    if ( isPhonetics )
    {
        QStringList     charList;
        u32             pos = 0;

        // make list of chars from naked string
        charList.reserve(word.size());
        for ( const auto& ch : word )
        {
            QString     currentCh;
            const auto& size = ch.text.at(_selected).size();

            for ( int i = 0; i < size; i++ )
                currentCh += _in.at(pos + i);

            charList.push_back(currentCh);
            pos += size;
        }


        for ( u32 i = 0; i < word.size(); i++ )
        {
            const auto& curWordSym  = word.at(i);
            const auto& curWordCh   = word.at(i).text.at(_selected);
            const auto& curCh       = charList.at(i);


            if ( curWordSym.phonetics == Phonetics::V )
            {
                // if there is char behind
                if ( i != 0 )
                {
                    const Symbol& prevWordSym = word.at(i - 1);


                    if ( this->__flags.useDoubleVowelSign && curCh == DoubleVowelSign )
                    {
                        if ( prevWordSym.phonetics == Phonetics::V )
                        {
                            if ( curWordSym.text.at(_selected) == prevWordSym.text.at(_selected) )
                                out += makeGreenHTML(curCh);
                            else out += makeRedHTML(curCh);

                            continue;
                        }
                    }
                    if ( this->__flags.useoi && curCh == DoubleVowelSign )
                    {
                        if ( prevWordSym.phonetics == Phonetics::CV )
                        {
                            if ( this->isGoodForOI(prevWordSym) )
                                out += makeGreenHTML(curCh);
                            else out += makeRedHTML(curCh);

                            continue;
                        }
                    }

                    out += pushSym(curCh, curWordCh);
                }
                else out += pushSym(curCh, curWordCh);
            }
            else if ( curWordSym.phonetics == Phonetics::CV )
            {
                out += pushSym(curCh, curWordCh);
            }
            else if ( curWordSym.phonetics == Phonetics::N )
            {
                out += pushSym(curCh, curWordCh);
            }
            else if ( curWordSym.phonetics == Phonetics::SmallTSU )
            {
                if ( i + 1 < word.size() )
                {
                    QString smallTsu;

                    smallTsu = charList.at(i + 1);
                    smallTsu.truncate(smallTsu.size() - 1);

                    out += pushSym(curCh, smallTsu);
                }
            }
        }
    }
    else
    {
        for ( int i = 0; i < _in.size(); i++ )
        {
            auto& sym = _in.at(i);

            if ( sym != str.at(i) )
            {
                out += makeRedHTML(sym);
            }
            else out += makeGreenHTML(sym);
        }
    }

    return out;
}
