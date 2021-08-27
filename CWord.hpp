#pragma once
#include "Settings.hpp"
#include "Kana.hpp"


class Word
{
public:
    void prepare( const Settings_s& _settings );

    Settings_s  getSettings( void ) const { return this->settings; };
    SymVec&     getSymList( void );
    SymVec&     getSymWord( void ) { return this->symWord; }
    Symbol      getRandomSym( PhoVec _selected = {} ) const;
    SymVec      getSubWord( PhoVec _selected = {} ) const;

    void    generateSymWord( void );
    void    makeSymList( void );

    bool    isGoodForOU( const Symbol& _sym ) const;


    Settings_s  settings;
    SymVec      symList;
    SymVec      symWord;

    void    addColumn( SymVec& _symVec, const SymVec& _col );
    void    addSymbol( SymVec& _symVec, const Symbol& _sym );
};
