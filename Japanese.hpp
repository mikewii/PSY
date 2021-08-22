#pragma once
#include <QString>
#include "Kana.hpp"

typedef uint32_t u32;
typedef uint64_t u64;
typedef uint8_t  u8;

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
        };
    };

    Japanese();


    void    generate( const Flags _flags );
    QString check( const QString& _in, SymbolEnum _selected ) const;

    QString getString( SymbolEnum _selected ) const;

private:
    QStringList     __strings;


    // random
    void initRandomEngine( void );
    u32  getRandom( u32 _min, u32 _max );


    void addColumn( std::vector<Symbol>& _symList, std::vector<Symbol>& _col );
    void addSymbol( std::vector<Symbol>& _symList, Symbol& _sym );
    void makeSymVec( std::vector<Symbol>& _symVec, const Flags& _flags );

    u32  removeTriplets( QString& _text );

};
