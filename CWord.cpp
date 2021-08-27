#include "CJapanese.hpp"
#include "CUtils.h"

void Word::generateSymWord( void )
{
    u32             wordLengthMax;
    u32             wordLengthCurrent = 0;


    if ( Word::settings.wordLengthRandom )
        wordLengthMax = Utils::getRandom(1, Word::settings.wordLengthLimit);
    else wordLengthMax = Word::settings.wordLength;


    for(;;)
    {
        if ( wordLengthCurrent == wordLengthMax ) break;

        const auto& sym = Word::getRandomSym();

        if ( Word::settings.preventDiDu )
        {
            const auto& di = Column4_D.at(1).text.at(Hiragana);
            const auto& du = Column4_D.at(2).text.at(Hiragana);

            if ( sym.text.at(Hiragana) == di || sym.text.at(Hiragana) == du )
                continue;
        }

        Word::symWord.push_back(sym);

        ++wordLengthCurrent;
    }
}


Symbol Word::getRandomSym( PhoVec _selected ) const
{
    if ( !_selected.empty() )
    {
        for(;;)
        {
            auto rand   = Utils::getRandom(0, Word::symList.size() - 1);
            auto sym    = Word::symList.at(rand);

            for ( auto& ph : _selected )
                if ( sym.phonetics == ph ) return sym;
        }
    }

    auto rand = Utils::getRandom(0, Word::symList.size() - 1);
    return Word::symList.at(rand);
}

//SymVec Word::getSubWord( u32 _wordLengthMax ) const
//{
//    SymVec  out;
//    auto    settings = this->__settings;
//    u32     toGet;
//    std::vector<Phonetics>  combination;


//    uint32_t variant = Utils::getRandom(0, 2);

//    if ( variant == 0 )
//        combination = {V,V};
//    else if ( variant == 1 )
//        combination = {CV,V};
//    else if ( variant == 2 )
//        combination = {CV,VV,V};
//    else if ( variant == 3 )
//        combination = {V,N};
//    else if ( variant == 4 )
//        combination = {SmallTSU,CV};


//    if ( _wordLengthMax > 3 )
//    {
//        if ( settings.useDoubleVowelSign )
//        {

//        }

//    }
//}


void Word::makeSymList( void )
{
    Word::symList.clear();
    Word::symWord.clear();

    Word::addColumn(Word::symList, Column1);

    if ( Word::settings.longConsonant ) Word::addSymbol(Word::symList, LongConsonant );
    if ( Word::settings.nn )            Word::addSymbol(Word::symList, NN );
    if ( Word::settings.col2_k ) Word::addColumn(Word::symList, Column2_K );
    if ( Word::settings.col2_g ) Word::addColumn(Word::symList, Column2_G );
    if ( Word::settings.col3_s ) Word::addColumn(Word::symList, Column3_S );
    if ( Word::settings.col3_z ) Word::addColumn(Word::symList, Column3_Z );
    if ( Word::settings.col4_t ) Word::addColumn(Word::symList, Column4_T );
    if ( Word::settings.col4_d ) Word::addColumn(Word::symList, Column4_D );
    if ( Word::settings.col5_n ) Word::addColumn(Word::symList, Column5_N );
    if ( Word::settings.col6_h ) Word::addColumn(Word::symList, Column6_H );
    if ( Word::settings.col6_b ) Word::addColumn(Word::symList, Column6_B );
    if ( Word::settings.col6_p ) Word::addColumn(Word::symList, Column6_P );
}

void Word::addColumn( SymVec& _symVec, const SymVec& _col )
{
    for ( auto& sym : _col )
        _symVec.push_back(sym);
}

void Word::addSymbol( SymVec& _symVec, const Symbol& _sym )
{
    _symVec.push_back(_sym);
}

void Word::prepare( const Settings_s& _settings )
{
    Word::settings = _settings;
    Word::makeSymList();
}

SymVec& Word::getSymList()
{
    return Word::symList;
}


bool Word::isGoodForOU( const Symbol& _sym ) const
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
