#include "CJapanese.hpp"
#include <random>
#include <time.h>


static std::mt19937 rng;


Japanese::Japanese()
{
    this->initRandomEngine();
}

void Japanese::generateSymWord( void )
{
    u32 wordLengthMax;
    u32 wordLengthCurrent = 0;


    if ( this->__settings.wordLengthRandom )
        wordLengthMax = this->getRandom(1, this->__settings.wordLengthLimit);
    else wordLengthMax = this->__settings.wordLength;


    for(;;)
    {
        if ( wordLengthCurrent == wordLengthMax ) break;

        const auto& sym = this->getRandomSym();

        if ( this->__settings.preventDiDu )
        {
            const auto& di = Column4_D.at(1).text.at(Hiragana);
            const auto& du = Column4_D.at(2).text.at(Hiragana);

            if ( sym.text.at(Hiragana) == di || sym.text.at(Hiragana) == du )
                continue;
        }

        this->__word.push_back(sym);

        ++wordLengthCurrent;
    }
}

void Japanese::generate( const Settings_s _settings )
{
    QString hiragana, katakana, phonetics_eng, phonetics_rus;
    auto&   symList = *(this->__symList = new SymVec);


    this->__settings = _settings;

    this->__word.clear();
    this->__strings.clear();
    this->makeSymVec(symList);
    this->__symList = &symList;


    /* generator */ this->generateSymWord();
    /* generator */
    /* generator */ this->grammarNN();
    /* generator */ this->grammarSmallTsu();
    /* generator */ this->grammarRemoveTriplets();

    delete this->__symList;

    for ( auto& sym : this->__word )
    {
        hiragana += sym.text.at(Hiragana);
        katakana += sym.text.at(Katakana);
    }

    phonetics_eng = this->makePhonetics(PhoneticsENG);
    phonetics_rus = this->makePhonetics(PhoneticsRUS);

    this->__strings.push_back(hiragana);
    this->__strings.push_back(katakana);
    this->__strings.push_back(phonetics_eng);
    this->__strings.push_back(phonetics_rus);
}

QString Japanese::getString( SymbolEnum _selected ) const
{
    if ( this->__strings.size() <= _selected ) return "getString() error!";
    else return this->__strings.at(_selected);
}

void Japanese::addColumn( SymVec& _symVec, std::vector<Symbol>& _col )
{
    for ( auto& sym : _col )
        _symVec.push_back(sym);
}

void Japanese::addSymbol( SymVec& _symVec, Symbol& _sym )
{
    _symVec.push_back(_sym);
}

void Japanese::initRandomEngine()
{
    rng.seed(time(NULL));
}

u32 Japanese::getRandom( u32 _min, u32 _max )
{
    if ( _max == 0 )
        _max = UINT32_MAX;
    std::uniform_int_distribution<u32>  uniform(_min, _max);

    return (uniform(rng));
}

Symbol Japanese::getRandomSym( Phonetics _restricted )
{
    if ( _restricted != Phonetics::NONE )
    {
        for(;;)
        {
            auto rand   = this->getRandom(0, this->__symList->size() - 1);
            auto sym    = this->__symList->at(rand);

            if ( _restricted & sym.phonetics ) return sym;
        }
    }

    auto rand = this->getRandom(0, this->__symList->size() - 1);
    return this->__symList->at(rand);
}

void Japanese::makeSymVec( SymVec& _symVec )
{
    auto& settings = this->__settings;


    this->addColumn(_symVec, Column1);

    if ( settings.longConsonant ) this->addSymbol(_symVec, LongConsonant );
    if ( settings.nn )            this->addSymbol(_symVec, NN );
    if ( settings.col2_k ) this->addColumn(_symVec, Column2_K );
    if ( settings.col2_g ) this->addColumn(_symVec, Column2_G );
    if ( settings.col3_s ) this->addColumn(_symVec, Column3_S );
    if ( settings.col3_z ) this->addColumn(_symVec, Column3_Z );
    if ( settings.col4_t ) this->addColumn(_symVec, Column4_T );
    if ( settings.col4_d ) this->addColumn(_symVec, Column4_D );
    if ( settings.col5_n ) this->addColumn(_symVec, Column5_N );
    if ( settings.col6_h ) this->addColumn(_symVec, Column6_H );
    if ( settings.col6_b ) this->addColumn(_symVec, Column6_B );
    if ( settings.col6_p ) this->addColumn(_symVec, Column6_P );
}
