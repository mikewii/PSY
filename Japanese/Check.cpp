#include "Japanese/Check.hpp"


static const QString    green  = "<span style='color:#00cc00;'>";
static const QString    red    = "<span style='color:#cc0000;'>";
static const QString    close  = "</span>";


QString makeRedHTML( const QString& _str ) { return red + _str + close; }
QString makeGreenHTML( const QString& _str ) { return green + _str + close; }


QString Check::pushSymbol( const QString& _symbol, const QString& _wordSym ) const
{
    if ( _symbol == _wordSym ) return makeGreenHTML(_symbol);
    else return makeRedHTML(_symbol);
}


QString Check::check( const QString& _in, const SymbolEnum _selected ) const
{
    QStringList     charList;
    u32             pos = 0;
    QString         out;
    auto            isPhonetics = _selected == PhoneticsENG || _selected == PhoneticsRUS;
    int             strSize = 0;
    bool            haveSubtitute = !Word::substitute.empty();


    for ( auto& sym : Word::symWord )
        strSize += sym.text.at(_selected).size();


    if ( !Check::alphabetCheck(_in, _selected) )
        return "Input must be in language selected for check!";
    if ( _in.size() != strSize )
        return "Input and word lenght doesnt match!";


    if ( isPhonetics )
    {
        // make list of chars from naked string
        charList.reserve(Word::symWord.size());
        for ( const auto& sym : Word::symWord )
        {
            QString         currentCh;
            const auto&     size = sym.text.at(_selected).size();


            for ( int i = 0; i < size; i++ )
                currentCh += _in.at(pos + i);

            charList.push_back(currentCh);
            pos += size;
        }


        for ( u32 i = 0; i < Word::symWord.size(); i++ )
        {
            //const auto& curWordSym  = Word::symWord.at(i);
            const auto& curWordCh   = Word::symWord.at(i).text.at(_selected);
            const auto& curCh       = charList.at(i);
            QString     subStr      = "";
            bool        checkSub    = false;


            if ( haveSubtitute )
            {
                for ( const auto& sub : Word::substitute )
                {
                    if ( sub.first == i )
                    {
                        checkSub = true;
                        subStr = sub.second.text.at(_selected);
                    }
                }
            }

            if ( checkSub && curCh != ':' )
            {
                QString ch;

                if ( curCh == subStr )
                    ch = subStr;

                if ( curCh == curWordCh )
                    ch = curWordCh;

                out += Check::pushSymbol(curCh, ch);
            }
            else out += Check::pushSymbol(curCh, curWordCh);
        }
    }
    else
    {
        for ( int i = 0; i < _in.size(); i++ )
        {
            auto& sym = _in.at(i);

            if ( sym != Word::strings.at(_selected).at(i) )
            {
                out += makeRedHTML(sym);
            }
            else out += makeGreenHTML(sym);
        }
    }

    return out;
}


bool Check::alphabetCheck( const QString& _text, const SymbolEnum _selected) const
{
    static const QString russian[] =
    {
        "а", "б", "в", "г", "д", "е",
        "ё", "ж", "з", "и", "й", "к",
        "л", "м", "н", "о", "п", "р",
        "с", "т", "у", "ф", "х", "ц",
        "ч", "ш", "щ", "ъ", "ы", "ь",
        "э", "ю", "я"
    };

    static const QString english[] =
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
        &KanaVowels,
        &KanaK,
        &KanaSpecialG,
        &KanaS,
        &KanaSpecialZ,
        &KanaT,
        &KanaSpecialD,
        &KanaN,
        &KanaH,
        &KanaSpecialB,
        &KanaSpecialP,
        &KanaM,
        &KanaY,
        &KanaR,
        &KanaW,
        &KanaSmallY
    };

    const std::vector<const Symbol*> japaneseSpecial =
    {
        &SmallTsu,
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
        if ( textChar == DoubleVowelSign.text.at(_selected) )
            ++count;
    }


    return count == _text.size();
}
