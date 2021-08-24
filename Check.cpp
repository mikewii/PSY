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

    if ( _in.size() != str.size() )
        return "Wrong word size!";
    if ( !this->alphabetCheck(_in, _selected) )
        return "Text must be in language selected for check!";


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
                        else if ( prevWordSym.phonetics == Phonetics::CV )
                        {
                            out += makeGreenHTML(curCh);
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


bool Japanese::isGoodForOI( const Symbol& _sym ) const
{
    if ( _sym.text.at(Hiragana) == Column2_K.at(4).text.at(Hiragana)) return true;
    if ( _sym.text.at(Hiragana) == Column2_G.at(4).text.at(Hiragana)) return true;
    if ( _sym.text.at(Hiragana) == Column3_S.at(4).text.at(Hiragana)) return true;
    if ( _sym.text.at(Hiragana) == Column3_Z.at(4).text.at(Hiragana)) return true;
    if ( _sym.text.at(Hiragana) == Column4_T.at(4).text.at(Hiragana)) return true;
    if ( _sym.text.at(Hiragana) == Column4_D.at(4).text.at(Hiragana)) return true;
    if ( _sym.text.at(Hiragana) == Column5_N.at(4).text.at(Hiragana)) return true;
    if ( _sym.text.at(Hiragana) == Column6_H.at(4).text.at(Hiragana)) return true;
    if ( _sym.text.at(Hiragana) == Column6_B.at(4).text.at(Hiragana)) return true;
    if ( _sym.text.at(Hiragana) == Column6_P.at(4).text.at(Hiragana)) return true;

    return false;
}


bool Japanese::alphabetCheck( const QString& _text, const SymbolEnum _selected) const
{
    static const std::vector<const char*> russian =
    {
        "а", "б", "в", "г", "д", "е",
        "ё", "ж", "з", "и", "й", "к",
        "л", "м", "н", "о", "п", "р",
        "с", "т", "у", "ф", "х", "ц",
        "ч", "ш", "щ", "ъ", "ы", "ь",
        "э", "ю", "я"
    };

    static const std::vector<const char*> english =
    {
        "a", "b", "c", "d", "e",
        "f", "g", "h", "i", "j",
        "k", "l", "m", "n", "o",
        "p", "q", "r", "s", "t",
        "u", "v", "w",
        "x", "y", "z"
    };


    const std::vector<const SymVec*> japanese =
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

    const std::vector<const Symbol*> japaneseSpecial =
    {
        &LongConsonant,
        &NN
    };

    int count = 0;
    switch( _selected )
    {
    case Hiragana:
    case Katakana:
    {
        for ( const auto& textChar : _text )
        {
            bool hit = false;


            for ( const auto& column : japanese)
            {
                for ( const auto& alphaChar : *column )
                {
                    if ( textChar == alphaChar.text.at(_selected) )
                    {
                        ++count;
                        hit = true;
                        break;
                    }
                }

                if ( hit ) break;
            }


            for( const auto& sym : japaneseSpecial )
            {
                if ( textChar == sym->text.at(_selected) )
                {
                    ++count;
                    break;
                }
            }
        }

        break;
    }
    case PhoneticsENG:
    {
        for ( const auto& textChar : _text )
        {
            for ( const auto& alphaChar : english )
            {
                if ( textChar == alphaChar )
                {
                    ++count;
                    break;
                }
            }
        }

        break;
    }
    case PhoneticsRUS:
    {
        for ( const auto& textChar : _text )
        {
            for ( const auto& alphaChar : russian )
            {
                if ( textChar == alphaChar )
                {
                    ++count;
                    break;
                }
            }
        }

        break;
    }
    default:break;
    }


    for ( const auto& textChar : _text )
    {
        if ( textChar == DoubleVowelSign )
            ++count;
    }


    return count == _text.size();
}
