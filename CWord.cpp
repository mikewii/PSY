#include "CJapanese.hpp"
#include "CUtils.h"

void Word::generateSymWord( void )
{
    u32             wordLengthMax;
    u32             wordLengthCurrent = 0;
    const auto&     settings = this->__settings;
    auto&           word = this->__word;


    if ( settings.wordLengthRandom )
        wordLengthMax = Utils::getRandom(1, settings.wordLengthLimit);
    else wordLengthMax = settings.wordLength;


    for(;;)
    {
        if ( wordLengthCurrent == wordLengthMax ) break;

        const auto& sym = this->getRandomSym();

        if ( settings.preventDiDu )
        {
            const auto& di = Column4_D.at(1).text.at(Hiragana);
            const auto& du = Column4_D.at(2).text.at(Hiragana);

            if ( sym.text.at(Hiragana) == di || sym.text.at(Hiragana) == du )
                continue;
        }

        word.push_back(sym);

        ++wordLengthCurrent;
    }
}


Symbol Word::getRandomSym( Phonetics _restricted ) const
{
    const auto& symList = this->__symList;


    if ( _restricted != Phonetics::NONE )
    {
        for(;;)
        {
            auto rand   = Utils::getRandom(0, symList.size() - 1);
            auto sym    = symList.at(rand);

            if ( _restricted & sym.phonetics ) return sym;
        }
    }

    auto rand = Utils::getRandom(0, symList.size() - 1);
    return symList.at(rand);
}


void Word::makeSymList( void )
{
    const auto& settings    = this->__settings;
    auto&       _symVec     = this->getSymList();

    _symVec.clear();
    this->__word.clear();

    this->addColumn(_symVec, Column1);

    if ( settings.longConsonant ) this->addSymbol(_symVec, LongConsonant );
    if ( settings.nn )            this->addSymbol(_symVec, NN );
    if ( settings.col2_k ) this->addColumn(_symVec, Column2_K );
    if ( settings.col2_g ) this->addColumn(_symVec, Column2_G );
    if ( settings.col3_s ) this->addColumn(_symVec, Column3_S );
    if ( settings.col3_z ) this->addColumn(_symVec, Column3_Z );
    if ( settings.col4_t ) this->addColumn(_symVec, Column4_T );
    if ( settings.col4_d ) this->addColumn(_symVec, Column4_D );
    if ( settings.col5_n ) this->addColumn(_symVec, Column5_N );
    if ( settings.col6_h ) this->addColumn(_symVec, Column6_H );
    if ( settings.col6_b ) this->addColumn(_symVec, Column6_B );
    if ( settings.col6_p ) this->addColumn(_symVec, Column6_P );
}

void Word::addColumn( SymVec& _symVec, std::vector<Symbol>& _col )
{
    for ( auto& sym : _col )
        _symVec.push_back(sym);
}

void Word::addSymbol( SymVec& _symVec, Symbol& _sym )
{
    _symVec.push_back(_sym);
}

SymVec& Word::getSymList()
{
    return this->__symList;
}


bool Word::isGoodForOI( const Symbol& _sym ) const
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
