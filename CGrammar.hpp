#pragma once
#include "CWord.hpp"

class Grammar : virtual public Word
{
public:
    void grammarSmallTsu( void );
    void grammarNN( void );
    void grammarRemoveTriplets( void );
};
