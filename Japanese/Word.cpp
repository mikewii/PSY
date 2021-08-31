#include "Japanese/Word.hpp"
#include "Utils.h"


void Word::pushSymbol( void )
{
    const auto& sym = Word::getRandomSym(Word::defaultPhoVec);

    Word::symWord.push_back(sym);
    Word::wordLengthCurrent += 1;
}

bool Word::pushSyllable()
{
    const auto& symVec = Word::getSymSyllable();

    if ( !symVec.empty() )
    {
        for ( auto& sym : symVec )
        {
            Word::symWord.push_back(sym);

            if ( sym.phonetics == CVD ) Word::wordLengthCurrent += 2;
            else Word::wordLengthCurrent += 1;
        }

        return true;
    }
    else return false;
}

void Word::generateSymWord( void )
{
    if ( Word::settings.wordLengthRandom )
        Word::wordLengthMax = Utils::getRandom(1, Word::settings.wordLengthLimit);
    else Word::wordLengthMax = Word::settings.wordLength;

    while( Word::wordLengthCurrent < Word::wordLengthMax )
    {
        if ( Word::wordLengthMax - 1 == Word::wordLengthCurrent )
            Word::defaultPhoVec.push_back(Phonetics::N);


        if ( Utils::getRandomBool() )
        {
            if ( !Word::pushSyllable() )
                Word::pushSymbol();
        }
        else Word::pushSymbol();
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

    auto selected = 0;


    for(;;)
    {
        auto repeat = false;
        selected = Utils::getRandom(0, pho.size() - 1);

        for ( const auto& ph : pho.at(selected) )
        {
            if ( !Word::settings.nn && ph == Phonetics::N ) repeat = true;
            if ( !Word::settings.col8_y && ph == Phonetics::D ) repeat = true;
            if ( !Word::settings.col8_y && ph == Phonetics::CVD ) repeat = true;
            if ( !Word::settings.smallTsu && ph == Phonetics::SmallTSU ) repeat = true;
            if ( Word::wordLengthCurrent == 0 && ph == Phonetics::SmallTSU ) repeat = true;
        }

        if ( repeat ) continue;
        else break;
    }


    return pho.at(selected);
}

void Word::makeKanaStrings()
{
    QString hiragana, katakana;

    for ( auto& sym : Word::symWord )
    {
        hiragana += sym.text.at(Hiragana);
        katakana += sym.text.at(Katakana);
    }

    Word::strings.push_back(hiragana);
    Word::strings.push_back(katakana);
}

bool Word::isBanned( const Symbol& _sym ) const
{
    for ( const auto& ban : Word::banned )
    {
        if ( _sym.text.at(Hiragana) == ban.text.at(Hiragana) ) return true;
    }

    return false;
}

void Word::initBanned( void )
{
    Word::banned.clear();

    if ( Word::settings.preventDiDu )
    {
        const Symbol& di    = KanaSpecialD.at(1);
        const Symbol& du    = KanaSpecialD.at(2);
        const SymVec& di_d  = KanaExtraD;


        banned.push_back(di);
        banned.push_back(du);

        for ( const auto& sym : di_d )
            banned.push_back(sym);
    }

    if ( Word::settings.preventObsoleteW )
    {
        const Symbol& wi    = KanaW.at(1);
        const Symbol& we    = KanaW.at(2);


        banned.push_back(wi);
        banned.push_back(we);
    }
}


SymVec Word::getSymSyllable( void ) const
{
    SymVec      out;
    PhoVec      combo;
    u32         spaceLeft = Word::wordLengthMax - Word::wordLengthCurrent;


    if ( spaceLeft < 3 || !Word::haveCV )
        return out;


    combo = Word::getSyllablePhonetics();

    for ( auto& pho : combo )
    {
        auto sym = Word::getRandomSym({pho});

        out.push_back(sym);
    }


    return out;
}


void Word::makeSymList( void )
{
    auto useExtra = Word::settings.col8_y;


    Word::symList.clear();
    Word::symWord.clear();


    Word::addColumn(KanaVowels);

    if ( Word::settings.smallTsu )  Word::addSymbol(SmallTsu);
    if ( Word::settings.nn )        Word::addSymbol(NN);

    if ( Word::settings.col2_k )
    {
        Word::haveCV = true;
        Word::addColumn(KanaK);
        if ( useExtra ) Word::addColumn(KanaExtraK);
    }
    if ( Word::settings.col2_g )
    {
        Word::haveCV = true;
        Word::addColumn(KanaSpecialG);
        if ( useExtra ) Word::addColumn(KanaExtraG);
    }
    if ( Word::settings.col3_s )
    {
        Word::haveCV = true;
        Word::addColumn(KanaS);
        if ( useExtra ) Word::addColumn(KanaExtraS);
    }
    if ( Word::settings.col3_z )
    {
        Word::haveCV = true;
        Word::addColumn(KanaSpecialZ);
        if ( useExtra ) Word::addColumn(KanaExtraZ);
    }
    if ( Word::settings.col4_t )
    {
        Word::haveCV = true;
        Word::addColumn(KanaT);
        if ( useExtra ) Word::addColumn(KanaExtraT);
    }
    if ( Word::settings.col4_d )
    {
        Word::haveCV = true;
        Word::addColumn(KanaSpecialD);
        if ( useExtra ) Word::addColumn(KanaExtraD);
    }
    if ( Word::settings.col5_n )
    {
        Word::haveCV = true;
        Word::addColumn(KanaN);
        if ( useExtra ) Word::addColumn(KanaExtraN);
    }
    if ( Word::settings.col6_h )
    {
        Word::haveCV = true;
        Word::addColumn(KanaH);
        if ( useExtra ) Word::addColumn(KanaExtraH);
    }
    if ( Word::settings.col6_b )
    {
        Word::haveCV = true;
        Word::addColumn(KanaSpecialB);
        if ( useExtra ) Word::addColumn(KanaExtraB);
    }
    if ( Word::settings.col6_p )
    {
        Word::haveCV = true;
        Word::addColumn(KanaSpecialP);
        if ( useExtra ) Word::addColumn(KanaExtraP);
    }
    if ( Word::settings.col7_m )
    {
        Word::haveCV = true;
        Word::addColumn(KanaM);
        if ( useExtra ) Word::addColumn(KanaExtraM );
    }
    if ( Word::settings.col8_y ) Word::addColumn(KanaY);
    if ( Word::settings.col9_r )
    {
        Word::haveCV = true;
        Word::addColumn(KanaR);
        if ( useExtra ) Word::addColumn(KanaExtraR);
    }
    if ( Word::settings.col10_w )
    {
        Word::haveCV = true;
        Word::addColumn(KanaW);
        if ( useExtra ) Word::addColumn(KanaExtraW);
    }
}


void Word::addColumn( const SymVec& _col )
{
    for ( auto& sym : _col )
    {
        if ( Word::isBanned(sym) ) continue;

        Word::symList.push_back(sym);
    }
}

void Word::addSymbol( const Symbol& _sym )
{
    Word::symList.push_back(_sym);
}

uint32_t Word::getRowIndex( const Symbol& _sym ) const
{
    if ( _sym.flag & Flags::Row1 ) return 1;
    if ( _sym.flag & Flags::Row2 ) return 2;
    if ( _sym.flag & Flags::Row3 ) return 3;
    if ( _sym.flag & Flags::Row4 ) return 4;
    if ( _sym.flag & Flags::Row5 ) return 5;

    return 0;
}

uint32_t Word::getColIndex(const Symbol &_sym) const
{
    if ( _sym.flag & Flags::Col1 ) return 1;
    if ( _sym.flag & Flags::Col2 ) return 2;
    if ( _sym.flag & Flags::Col3 ) return 3;
    if ( _sym.flag & Flags::Col4 ) return 4;
    if ( _sym.flag & Flags::Col5 ) return 5;
    if ( _sym.flag & Flags::Col6 ) return 6;
    if ( _sym.flag & Flags::Col7 ) return 7;
    if ( _sym.flag & Flags::Col8 ) return 8;
    if ( _sym.flag & Flags::Col9 ) return 9;
    if ( _sym.flag & Flags::Col10 ) return 10;

    return 0;
}

void Word::run( const Settings_s& _settings )
{
    Word::wordLengthCurrent = 0;
    Word::defaultPhoVec     = {V,CV,D};
    Word::settings          = _settings;

    Word::strings.clear();
    Word::strings.reserve(4);

    Word::initBanned();
    Word::makeSymList();

    Word::generateSymWord();

    Word::makeKanaStrings();
}

bool Word::isGoodForOU( const Symbol& _sym ) const
{
    if ( _sym.flag & Flags::Row5 ) return true;

    return false;
}
