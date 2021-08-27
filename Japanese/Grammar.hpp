#pragma once
#include "Japanese/Word.hpp"

class Grammar : virtual public Word
{
public:
    void grammarSmallTsu( void );
    void grammarNN( void );
    void grammarRemoveTriplets( void );
};
