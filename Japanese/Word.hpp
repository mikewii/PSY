#pragma once
#include "Settings.hpp"
#include "Japanese/Kana.hpp"


class Word
{
public:
    void    prepare( const Settings_s& _settings );

    Symbol      getRandomSym( const PhoVec _selected = {} ) const;
    SymVec      getSymSyllable( void ) const;

    void    generateSymWord( void );
    void    makeSymList( void );

    bool    isGoodForOU( const Symbol& _sym ) const;

    void    addColumn( SymVec& _symVec, const SymVec& _col );
    void    addSymbol( SymVec& _symVec, const Symbol& _sym );


    Settings_s  settings;
    SymVec      symList;
    SymVec      symWord;

private:
    PhoVec      getSyllablePhonetics( void ) const;
    uint32_t    wordLengthMax = 0;

    bool        isBanned( const Symbol& _sym ) const;
};
