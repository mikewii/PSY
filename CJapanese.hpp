#pragma once
#include <QString>
#include "Kana.hpp"
#include "Settings.hpp"

class Japanese
{
public:
    Japanese();

    void    generate( const Settings_s _settings );
    QString check( const QString& _in, const SymbolEnum _selected ) const;

    QString getString( SymbolEnum _selected ) const;

private:
    Settings_s  __settings;
    QStringList __strings;
    SymVec*     __symList;
    SymVec      __word;

    // random
    void    initRandomEngine( void );
    u32     getRandom( u32 _min, u32 _max );
    Symbol  getRandomSym( Phonetics _restricted = NONE );


    void addColumn( SymVec& _symVec, SymVec& _col );
    void addSymbol( SymVec& _symVec, Symbol& _sym );
    void makeSymVec( SymVec& _symVec );

    void generateSymWord( void );

    // grammar functions
    void grammarSmallTsu( void );
    void grammarNN( void );
    void grammarRemoveTriplets( void );

    // phonetics functions
    QString     makePhonetics( const SymbolEnum _selected ) const;
    bool        isGoodForOI( const Symbol& _sym ) const;
    bool        alphabetCheck( const QString& _text, const SymbolEnum _selected ) const;

};
