#pragma once
#include <QString>
#include "Kana.hpp"

typedef uint32_t u32;
typedef uint64_t u64;

class Japanese
{
public:

    union Flags {
        u32 raw;
        struct {
            u32 maxLength : 8;
            u32 maxSymbolsRandom : 1;
            u32 preventTriplets : 1;

            u32 col2_k : 1;
            u32 col2_g : 1;
            u32 col3_s : 1;
            u32 col3_z : 1;
            u32 col4_t : 1;
            u32 col4_d : 1;
            u32 col5_n : 1;
            u32 col6_h : 1;
            u32 col6_b : 1;
            u32 col6_p : 1;

            u32 longConsonants : 1;
            u32 nn : 1;
        };
    };

    Japanese();


    void    generate( Flags _flags, u32 _maxSymbols );
    QString check( const QString& _in, SymbolEnum _selected ) const;

    QString getString( SymbolEnum _selected ) const;

private:
    QStringList     __strings;


    // random
    void initRandomEngine( void );
    u32  getRandom( u32 _min, u32 _max );


    void addColumn( std::vector<Symbol>& _symList, std::vector<Symbol>& _col );
    void addSymbol( std::vector<Symbol>& _symList, Symbol& _sym );
    void makeSymVec( std::vector<Symbol>& _symVec, Flags& _flags );

    u32  removeTriplets( QString& _text );

};
