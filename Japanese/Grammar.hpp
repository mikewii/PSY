#pragma once
#include "Japanese/Word.hpp"

class Grammar : virtual public Word
{
public:
    void run( void );

    void    scan( void );
    void    removeTriplets( void );

private:
    uint32_t    hit = 0;
    uint32_t    pos = 0;

    void    scanForSelectedPhoVec( const PhoVec& _phoVec );
    bool    check( const Symbol& _sym, const Phonetics& _pho );


    void    doubleVowel( const Symbol& _first, const Symbol& _second );
    void    NNMM( const Symbol& _second );
    void    smallTsu( const Symbol& _second );
};
