#include "Japanese.hpp"
#include <random>
#include <time.h>


static std::mt19937 rng;

Japanese::Japanese()
{
    this->initRandomEngine();
}

u32 Japanese::removeTriplets( QString& _text )
{
    std::vector<int>    pos;

    // find
    for ( int i = 0; i < _text.size(); i++ )
    {
        u32 hit = 0;
        const auto& ch = _text.at(i);


        for ( int j = 0; j < _text.size(); j++ )
        {
            const auto& ch2 = _text.at(j);

            if ( ch2 == ch ) ++hit;
            if ( hit > 2 )
            {
                bool fine = true;

                for ( auto& element : pos )
                {
                    if ( j == element ) fine = false;
                }

                if ( fine) pos.push_back(j);
                --hit;
            }
        }
    }


    if ( !pos.empty() )
        std::sort(pos.begin(), pos.end(), [](int a, int b) { return a > b; });


    //remove triplets
    for ( auto& i : pos )
    {
        _text.remove(i, 1);
    }

    return pos.size();
}

void Japanese::generate( const Flags _flags )
{
    std::vector<Symbol>     symWord;
    std::vector<Symbol>     symList;
    u32                     wordLengthMax;

// triplets leftovers
//    u32         symbolsLeft = 0;
//    int         tripletsMinSymbolsLimit = _flags.maxLength / 2;


    this->__strings.clear();
    this->makeSymVec(symList, _flags);

    if ( _flags.wordLengthRandom )
        wordLengthMax = this->getRandom(1, _flags.wordLengthLimit);
    else wordLengthMax = _flags.wordLength;


    u32     wordLengthCurrent   = 0;
    bool    nextIsCV            = false;
    for(;;)
    {
        if ( wordLengthCurrent == wordLengthMax ) break;

        u32     rand        = this->getRandom(0, symList.size() - 1);
        Symbol& selected    = symList.at(rand);


        if ( nextIsCV ) // smallTsu follows with consonant
        {
            if ( selected.phonetic != Phonetics::CV ) continue;
            else nextIsCV = false;
        }

        if ( selected.phonetic == LongConsonant.phonetic  ) // smallTsu cant be at begining or end of word
        {
            if ( wordLengthMax > 2 )
            {
                if ( wordLengthCurrent == 0 ) continue;
                if ( wordLengthCurrent + 1 == wordLengthMax ) continue;

                nextIsCV = true;
            }
        }

        if ( selected.phonetic == NN.phonetic ) // N only at end of word
        {
            if ( wordLengthCurrent + 1 != wordLengthMax ) continue;
            if ( wordLengthMax == 1 ) continue;
        }


        symWord.push_back(selected);
        ++wordLengthCurrent;
    }


    QString hiragana, katakana, phonetics_eng, phonetics_rus;
    for ( auto& sym : symWord )
    {
        hiragana += sym.text.at(Hiragana);
        katakana += sym.text.at(Katakana);

    }

    this->__strings.push_back(hiragana);
    this->__strings.push_back(katakana);
}

QString Japanese::check( const QString& _in, SymbolEnum _selected ) const
{
    static const QString    green  = "<span style='color:#00cc00;'>";
    static const QString    red    = "<span style='color:#cc0000;'>";
    static const QString    close  = "</span>";


    QString         out;
    const QString&  str = this->getString(_selected);

    for ( int i = 0; i < _in.size(); i++ )
    {
        if ( _in.at(i) != str.at(i) )
        {
            out += red + _in.at(i) + close;
        }
        else out += green + _in.at(i) + close;
    }

    return out;
}

QString Japanese::getString( SymbolEnum _selected ) const
{
    if ( this->__strings.size() <= _selected ) return "getString() error!";
    else return this->__strings.at(_selected);
}

void Japanese::addColumn( std::vector<Symbol>& _symList, std::vector<Symbol>& _col )
{
    for ( auto& sym : _col )
        _symList.push_back(sym);
}

void Japanese::addSymbol( std::vector<Symbol>& _symList, Symbol& _sym )
{
    _symList.push_back(_sym);
}

void Japanese::initRandomEngine()
{
    rng.seed(time(NULL));
}

u32 Japanese::getRandom( u32 _min, u32 _max )
{
    if ( _max == 0 )
        _max = UINT32_MAX;
    std::uniform_int_distribution<u32>  uniform(_min, _max);

    return (uniform(rng));
}

void Japanese::makeSymVec( std::vector<Symbol>& _symVec, const Flags& _flags )
{
    this->addColumn(_symVec, Column1);

    if ( _flags.longConsonant )    this->addSymbol(_symVec, LongConsonant );
    if ( _flags.nn )                this->addSymbol(_symVec, NN );
    if ( _flags.col2_k ) this->addColumn(_symVec, Column2_K );
    if ( _flags.col2_g ) this->addColumn(_symVec, Column2_G );
    if ( _flags.col3_s ) this->addColumn(_symVec, Column3_S );
    if ( _flags.col3_z ) this->addColumn(_symVec, Column3_Z );
    if ( _flags.col4_t ) this->addColumn(_symVec, Column4_T );
    if ( _flags.col4_d ) this->addColumn(_symVec, Column4_D );
    if ( _flags.col5_n ) this->addColumn(_symVec, Column5_N );
    if ( _flags.col6_h ) this->addColumn(_symVec, Column6_H );
    if ( _flags.col6_b ) this->addColumn(_symVec, Column6_B );
    if ( _flags.col6_p ) this->addColumn(_symVec, Column6_P );
}
