#include "Japanese/Word.hpp"
#include "Utils.h"

void Word::generateSymWord( void )
{
    u32             wordLengthCurrent = 0;


    if ( Word::settings.wordLengthRandom )
        Word::wordLengthMax = Utils::getRandom(1, Word::settings.wordLengthLimit);
    else Word::wordLengthMax = Word::settings.wordLength;


    for(;;)
    {
        if ( wordLengthCurrent == Word::wordLengthMax ) break;

        auto useSyllable = Utils::getRandom(0, 1);


        if ( useSyllable == 1 )
        {
            const auto& symVec = Word::getSymSyllable();

            if ( !symVec.empty() )
            {
                for ( auto& sym : symVec )
                {
                    Word::symWord.push_back(sym);
                    ++wordLengthCurrent;
                }
            }
        }
        else
        {
            const auto& sym = Word::getRandomSym();

            Word::symWord.push_back(sym);
            ++wordLengthCurrent;
        }
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

PhoVec Word::getSyllable( void ) const
{
    switch (Utils::getRandom(0, 8)) {
    case 0: return {V,V};
    case 1: return {CV,V};
    case 2: return {V,D};
    case 3: return {CV,D};
    case 4: return {CVD};
    case 5: return {CVD,V};
    case 6: return {V,N};
    case 7: return {CV,N};
    case 8: return {SmallTSU,CV};
    default:break;
    }

    return {V,V};
}

SymVec Word::getSymSyllable( void ) const
{
    SymVec      out;
    PhoVec      combo;
    u32         spaceLeft = Word::wordLengthMax - Word::symWord.size();


    if ( spaceLeft < 2 )
        return out;


    for(;;)
    {
        combo = Word::getSyllable();

        for ( auto& pho : combo )
        {
            if ( !Word::settings.nn && pho == Phonetics::N ) continue;
            if ( !Word::settings.smallTsu && pho == Phonetics::SmallTSU ) continue;
            if ( !Word::settings.col8_y && pho == Phonetics::CVD ) continue;
        }

        break;
    }


    for ( auto& pho : combo )
    {
        auto sym = Word::getRandomSym({pho});

        out.push_back(sym);
    }


    return out;
}


void Word::makeSymList( void )
{
    auto useDiphtongs = Word::settings.col8_y;

    Word::symList.clear();
    Word::symWord.clear();

    Word::addColumn(Word::symList, Column1);

    if ( Word::settings.smallTsu )  Word::addSymbol(Word::symList, SmallTsu );
    if ( Word::settings.nn )        Word::addSymbol(Word::symList, NN );

    if ( Word::settings.col2_k )
    {
        Word::addColumn(Word::symList, Column2_K );
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column2_K_D );
    }
    if ( Word::settings.col2_g )
    {
        Word::addColumn(Word::symList, Column2_G );
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column2_G_D );
    }
    if ( Word::settings.col3_s )
    {
        Word::addColumn(Word::symList, Column3_S );
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column3_S_D );
    }
    if ( Word::settings.col3_z )
    {
        Word::addColumn(Word::symList, Column3_Z );
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column3_Z_D );
    }
    if ( Word::settings.col4_t )
    {
        Word::addColumn(Word::symList, Column4_T );
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column4_T_D );
    }
    if ( Word::settings.col4_d )
    {
        Word::addColumn(Word::symList, Column4_D );
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column4_D_D );
    }
    if ( Word::settings.col5_n )
    {
        Word::addColumn(Word::symList, Column5_N );
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column5_N_D );
    }
    if ( Word::settings.col6_h )
    {
        Word::addColumn(Word::symList, Column6_H );
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column6_H_D );
    }
    if ( Word::settings.col6_b )
    {
        Word::addColumn(Word::symList, Column6_B );
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column6_B_D );
    }
    if ( Word::settings.col6_p )
    {
        Word::addColumn(Word::symList, Column6_P );
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column6_P_D );
    }
    if ( Word::settings.col7_m )
    {
        Word::addColumn(Word::symList, Column7_M );
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column7_M_D );
    }
    if ( Word::settings.col8_y ) Word::addColumn(Word::symList, Column8_Y );
}

void Word::addColumn( SymVec& _symVec, const SymVec& _col )
{
    for ( auto& sym : _col )
    {
        if ( Word::settings.preventDiDu )
        {
            const auto& di = Column4_D.at(1).text.at(Hiragana);
            const auto& du = Column4_D.at(2).text.at(Hiragana);
            const auto& ch = sym.text.at(Hiragana);

            if ( ch == di || ch == du ) continue;

            for ( const auto& s : Column4_D_D )
                if ( ch == s.text.at(Hiragana) ) continue;
        }

        _symVec.push_back(sym);
    }
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
    if ( _sym.text.at(Hiragana) == Column7_M.at(4).text.at(Hiragana)) return true;
    if ( _sym.text.at(Hiragana) == Column8_Y.at(2).text.at(Hiragana)) return true;

    return false;
}
