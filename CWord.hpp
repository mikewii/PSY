#pragma once
#include "Settings.hpp"
#include "Kana.hpp"


class Word
{
public:
    Word&       getWord( void ) { return *this; }


    Settings_s  getSettings( void ) const { return this->__settings; };
    SymVec&     getSymList( void );
    SymVec&     getSymWord( void ) { return this->__word; }
    Symbol      getRandomSym( Phonetics _restricted = NONE ) const;

    void    generateSymWord( void );
    void    makeSymList( void );

    void    setSettings( const Settings_s& _settings ) { this->__settings = _settings; }

    bool    isGoodForOI( const Symbol& _sym ) const;

private:
    Settings_s  __settings;
    SymVec      __symList;
    SymVec      __word;

    void    addColumn( SymVec& _symVec, SymVec& _col );
    void    addSymbol( SymVec& _symVec, Symbol& _sym );
};
