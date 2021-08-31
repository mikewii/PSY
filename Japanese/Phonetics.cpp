#include "Japanese/Phonetics.hpp"


void PhoneticsGenerator::run()
{
    QString eng, rus;

    eng = PhoneticsGenerator::makePhonetics(PhoneticsENG);
    rus = PhoneticsGenerator::makePhonetics(PhoneticsRUS);

    Word::strings.push_back(eng);
    Word::strings.push_back(rus);
}

QString PhoneticsGenerator::makePhonetics( const SymbolEnum _selected )
{
    QString     out;
    bool        haveSubstitute = !Word::substitute.empty();

    for ( u32 i = 0; i < Word::symWord.size(); i++ )
    {
        bool        skip = false;

        if ( haveSubstitute )
        {
            for ( const auto& sub : Word::substitute )
            {
                if ( i == sub.first ) // then push substitute
                {
                    out += sub.second.text.at(_selected);
                    skip = true;
                }
            }
        }

        if ( skip ) continue;
        else out += Word::symWord.at(i).text.at(_selected);
    }

    return out;
}
