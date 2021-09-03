#include "Japanese/Grammar.hpp"


void Grammar::run()
{
    Word::substitute.clear();

    Grammar::scan();
    Grammar::removeTriplets();
}


bool Grammar::check( const Symbol& _sym, const Phonetics& _pho )
{
    auto res = _sym.phonetics == _pho;

    if ( res ) Grammar::hit += 1;
    else if ( !res && Grammar::hit == 1 )
    {
        Grammar::hit = 0;
        Grammar::pos -= 1;
    }
    else Grammar::hit = 0;

    return res;
}

void Grammar::doubleVowel( const Symbol& _first, const Symbol& _second )
{
    if ( Word::settings.useDoubleVowelSign )
    {
        switch( _first.phonetics )
        {
        case Phonetics::V:
        {
            // aa ii > a: i:
            if ( _first.text.at(Hiragana) == _second.text.at(Hiragana) )
                Word::substitute.push_back({Grammar::pos, DoubleVowelSign});

            break;
        }
        case Phonetics::CV:
        {
            // kou gou > ko: go:
            if ( Word::getRowIndex(_first) == 5 && Word::getRowIndex(_second) == 3 )
                Word::substitute.push_back({Grammar::pos, DoubleVowelSign});

            // kaa gaa > ka: ga:  but koo > koo
            else if ( Word::getRowIndex(_first) == Word::getRowIndex(_second) && Word::getRowIndex(_second) != 5 )
                Word::substitute.push_back({Grammar::pos, DoubleVowelSign});

            break;
        }
        case Phonetics::D:
        case Phonetics::CVD:
        {
            // jou juu > jo: ju:
            if ( Word::getRowIndex(_first) == 3 || Word::getRowIndex(_first) == 5 )
            {
                if ( Word::getRowIndex(_second) == 3 )
                    Word::substitute.push_back({Grammar::pos, DoubleVowelSign});
            }

            // joo jaa > jo: ja: // lets avoid confusion for now
            //else if ( Word::getRowIndex(_first) == Word::getRowIndex(_second) )
            //    Word::substitute.push_back({Grammar::pos, DoubleVowelSign});

            // jaa > ja:
            else
            {
                if ( Word::getRowIndex(_second) == 1 )
                    Word::substitute.push_back({Grammar::pos, DoubleVowelSign});
            }

            break;
        }
        default:break;
        }
    }
}

void Grammar::NNMM( const Symbol& _second )
{
    if ( true ) // add option later?
    {
        // column M
        if ( Word::getColIndex(_second) == 7 )
            Word::substitute.push_back({Grammar::pos - 1, MM});
        // columns P B
        else if ( _second.flag & Flags::Special && Word::getColIndex(_second) == 6 )
            Word::substitute.push_back({Grammar::pos - 1, MM});
    }
}

void Grammar::smallTsu( const Symbol& _second )
{
    auto    eng = _second.text.at(PhoneticsENG).at(0);
    auto    rus = _second.text.at(PhoneticsRUS).at(0);
    Symbol  smallTSU = {{"","",eng,rus},{},{}};

    Word::substitute.push_back({Grammar::pos - 1, smallTSU});
}


void Grammar::scan()
{
    static const std::vector<PhoVec> lookFor =
    {
        {V,V},
        {CV,V},
        {CVD,V},
        {D,V},
        {N,CV},
        {SmallTSU,CV},
        {SmallTSU,CVD}
    };

    for ( const auto& phoVec : lookFor )
        Grammar::scanForSelectedPhoVec(phoVec);

}

void Grammar::scanForSelectedPhoVec( const PhoVec& _phoVec )
{
    for ( Grammar::pos = 0, Grammar::hit = 0; Grammar::pos < Word::symWord.size(); Grammar::pos++ )
    {
        const auto& sym = Word::symWord.at(Grammar::pos);


        switch( Grammar::hit )
        {

        case 0:
        {
            if ( Grammar::check(sym, _phoVec.at(Grammar::hit)) ) continue;
            break;
        }
        case 1:
        {
            if ( !Grammar::check(sym, _phoVec.at(Grammar::hit)) ) continue;

            Grammar::hit = 0;

            const auto& firstSym    = Word::symWord.at(Grammar::pos - 1);
            const auto& secondSym   = Word::symWord.at(Grammar::pos);


            if ( secondSym.phonetics == V )
                Grammar::doubleVowel(firstSym, secondSym);

            if ( firstSym.phonetics == N )
                Grammar::NNMM(secondSym);

            if ( firstSym.phonetics == SmallTSU )
                Grammar::smallTsu(secondSym);

            break;
        }
        default:break;
        } // switch
    }
}

void Grammar::removeTriplets( void )
{
    Symbol  s;


    auto inGeneratorLimit   = Word::settings.wordLength / 2 <= Word::symList.size() + 2;
    auto acceptableWordSize = Word::settings.wordLength >= 3;
    if ( !Word::settings.preventTriplets || !inGeneratorLimit || !acceptableWordSize )
        return;


    for ( u32 i = 0; i < Word::symWord.size(); i++ )
    {
        auto&   sym = Word::symWord.at(i);


        if ( i + 2 < Word::symWord.size() )
        {
            // if we found double
            if ( sym.text.at(Hiragana) == Word::symWord.at(i + 1).text.at(Hiragana) )
            {
                // if we found triplet
                if ( sym.text.at(Hiragana) == Word::symWord.at(i + 2).text.at(Hiragana) )
                {
                    for(;;)
                    {
                        s = Word::getRandomSym({V,CV});

                        if ( sym.text.at(Hiragana) != s.text.at(Hiragana) ) break;
                    }

                    Word::symWord.at(i + 2) = s;
                }
            }
        }
    }
}


