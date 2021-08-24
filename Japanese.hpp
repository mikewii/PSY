#pragma once
#include <QString>
#include "Kana.hpp"

typedef uint32_t u32;
typedef uint64_t u64;
typedef uint8_t  u8;

// https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html#Common-Predefined-Macros
static const QString __timestamp = __TIMESTAMP__;

class Japanese
{
public:

    union Flags {
        using size = u64;

        size    raw{0};
        char    raw_byte[sizeof(size)];
        struct {
            size wordLength : 8;
            size wordLengthLimit : 8;
            size wordLengthRandom : 1;
            size preventTriplets : 1;
            size multipleColumn : 1;

            size col2_k : 1;
            size col2_g : 1;
            size col3_s : 1;
            size col3_z : 1;
            size col4_t : 1;
            size col4_d : 1;
            size col5_n : 1;
            size col6_h : 1;
            size col6_b : 1;
            size col6_p : 1;

            size longConsonant : 1;
            size nn : 1;

            // phonetics settings
            size useDoubleVowelSign : 1;
            size useoi : 1;
        };
    };

    Japanese();


    void    generate( const Flags _flags );
    QString check( const QString& _in, const SymbolEnum _selected ) const;

    QString getString( SymbolEnum _selected ) const;

private:
    Flags       __flags;
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

};
