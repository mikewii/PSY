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
            const auto& sym = Word::getRandomSym({V,CV,D});

            Word::symWord.push_back(sym);
            ++wordLengthCurrent;
        }
    }
}


Symbol Word::getRandomSym( const PhoVec _selected ) const
{
    if ( !_selected.empty() )
    {
        for(;;)
        {
            auto rand   = Utils::getRandom(0, Word::symList.size() - 1);
            auto sym    = Word::symList.at(rand);

            for ( const auto& ph : _selected )
                if ( sym.phonetics == ph ) return sym;
        }
    }

    auto rand = Utils::getRandom(0, Word::symList.size() - 1);
    return Word::symList.at(rand);
}


PhoVec Word::getSyllablePhonetics( void ) const
{
    static const std::vector<PhoVec> pho =
    {
        {V,V},
        {CV,V},
        {V,D},
        {CV,D},
        {CVD},
        {CVD,V},
        {V,N},
        {CV,N},
        {SmallTSU,CV}
    };

    auto selected = Utils::getRandom(0, pho.size() - 1);
    return pho.at(selected);
}

bool Word::isBanned( const Symbol& _sym ) const
{
    // di du flag
    const Symbol& di    = Column4_D.at(1);
    const Symbol& du    = Column4_D.at(2);
    const SymVec& di_d  = Column4_D_D;

    const Symbol aa[] = {di,du};




    //constexpr SymVec bannedDiDu = {};

    if ( Word::settings.preventDiDu )
    {
        if ( _sym.text.at(Hiragana) == di.text.at(Hiragana) ) return true;
        if ( _sym.text.at(Hiragana) == du.text.at(Hiragana) ) return true;

        for ( auto& sym : di_d )
            if ( _sym.text.at(Hiragana) == sym.text.at(Hiragana) ) return true;
    }


    return false;
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
        bool repeat = false;
        combo = Word::getSyllablePhonetics();


        for ( auto& pho : combo )
        {
            if ( !Word::settings.nn && pho == Phonetics::N ) repeat = true;
            if ( !Word::settings.smallTsu && pho == Phonetics::SmallTSU ) repeat = true;
            if ( !Word::settings.col8_y && pho == Phonetics::D ) repeat = true;
            if ( !Word::settings.col8_y && pho == Phonetics::CVD ) repeat = true;
        }

        if ( repeat ) continue;
        else break;
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
        Word::addColumn(Word::symList, Column2_K);
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column2_K_D);
    }
    if ( Word::settings.col2_g )
    {
        Word::addColumn(Word::symList, Column2_G);
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column2_G_D);
    }
    if ( Word::settings.col3_s )
    {
        Word::addColumn(Word::symList, Column3_S);
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column3_S_D);
    }
    if ( Word::settings.col3_z )
    {
        Word::addColumn(Word::symList, Column3_Z);
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column3_Z_D);
    }
    if ( Word::settings.col4_t )
    {
        Word::addColumn(Word::symList, Column4_T);
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column4_T_D);
    }
    if ( Word::settings.col4_d )
    {
        Word::addColumn(Word::symList, Column4_D);
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column4_D_D);
    }
    if ( Word::settings.col5_n )
    {
        Word::addColumn(Word::symList, Column5_N);
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column5_N_D);
    }
    if ( Word::settings.col6_h )
    {
        Word::addColumn(Word::symList, Column6_H);
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column6_H_D);
    }
    if ( Word::settings.col6_b )
    {
        Word::addColumn(Word::symList, Column6_B);
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column6_B_D);
    }
    if ( Word::settings.col6_p )
    {
        Word::addColumn(Word::symList, Column6_P);
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column6_P_D);
    }
    if ( Word::settings.col7_m )
    {
        Word::addColumn(Word::symList, Column7_M);
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column7_M_D );
    }
    if ( Word::settings.col8_y ) Word::addColumn(Word::symList, Column8_Y);
    if ( Word::settings.col9_r )
    {
        Word::addColumn(Word::symList, Column9_R);
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column9_R_D);
    }
    if ( Word::settings.col10_w )
    {
        Word::addColumn(Word::symList, Column10_W);
        if ( useDiphtongs ) Word::addColumn(Word::symList, Column10_W_D);
    }
}


void Word::addColumn( SymVec& _symVec, const SymVec& _col )
{
//    SymVec banned;

//    if ( Word::settings.preventDiDu )
//        banned += Column4_D_D;

    for ( auto& sym : _col )
    {
        if ( isBanned(sym) ) continue;

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
    if ( _sym.flags.row == 5 ) return true;

    return false;
}
