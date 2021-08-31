#pragma once
#include "Settings.hpp"
#include "Japanese/Kana.hpp"


class Word
{
public:
    void    run( const Settings_s& _settings );

    Symbol      getRandomSym( const PhoVec _selected = {} ) const;
    SymVec      getSymSyllable( void ) const;
    void        pushSymbol( void );
    bool        pushSyllable( void );

    void    generateSymWord( void );
    void    makeSymList( void );

    bool    isGoodForOU( const Symbol& _sym ) const;

    void    addColumn( const SymVec& _col );
    void    addSymbol( const Symbol& _sym );

    uint32_t    getRowIndex( const Symbol& _sym ) const;
    uint32_t    getColIndex( const Symbol& _sym ) const;


    uint32_t    wordLengthCurrent = 0;
    bool        haveCV = false;

    Settings_s  settings;
    SymVec      symList;
    SymVec      symWord;
    QStringList strings;
    PhoVec      defaultPhoVec;
    std::vector<std::pair<uint32_t, Symbol>>    substitute;

private:
    SymVec      banned;
    PhoVec      getSyllablePhonetics( void ) const;
    uint32_t    wordLengthMax = 0;

    void        makeKanaStrings( void );

    bool        isBanned( const Symbol& _sym ) const;
    void        initBanned( void );
};
