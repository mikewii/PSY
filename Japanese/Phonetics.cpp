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
    std::vector<uint32_t>   skipVec;
    uint32_t                prevSub = 0;

    // hacky way to skip subs that positioned too close to eachother
    for ( const auto& sub : Word::substitute )
    {
        if ( prevSub == 0 )
        {
            prevSub = sub.first;
            continue;
        }


        if ( prevSub + 1 == sub.first )
            skipVec.push_back(sub.first);

        prevSub = sub.first;
    }


    for ( u32 i = 0; i < Word::symWord.size(); i++ )
    {
        bool        skip = false;

        if ( haveSubstitute )
        {
            for ( const auto& sub : Word::substitute )
            {
                if ( i == sub.first && prevSub + 1 != sub.first ) // then push substitute
                {
                    for ( const auto& toSkip : skipVec )
                        if ( i == toSkip ) break;

                    out += sub.second.text.at(_selected);
                    skip = true;
                    prevSub = i;
                }
            }
        }

        if ( skip ) continue;
        else out += Word::symWord.at(i).text.at(_selected);
    }

    return out;
}
