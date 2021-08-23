#include "Japanese.hpp"


static const QString    green  = "<span style='color:#00cc00;'>";
static const QString    red    = "<span style='color:#cc0000;'>";
static const QString    close  = "</span>";


QString makeRedHTML( const QString& _str ) { return red + _str + close; }
QString makeGreenHTML( const QString& _str ) { return green + _str + close; }
QString pushSym( const QString& _symbol, const QString& _wordSym )
{
    if ( _symbol == _wordSym ) return makeGreenHTML(_symbol);
    else return makeRedHTML(_symbol);
}


std::pair<QString,bool> makeOI( QString _currentSym, QString _nextSym, QString _wordSym, SymbolEnum _selected )
{
    const QString&  sym_i   = Column1.at(1).text.at(_selected);
    QString         out;
    bool            skip = false;

    out += pushSym(_currentSym, _wordSym);

    if ( _nextSym == DoubleVowelSign || _nextSym == sym_i )
        out += makeGreenHTML(_nextSym);
    else out += makeRedHTML(_nextSym);

    skip = true;

    return {out, skip};
}

QString makeDoubleVowel( QString _currentSym, QString _nextSym )
{

}


QString Japanese::check( const QString& _in, SymbolEnum _selected ) const
{
    QString         out;
    const QString&  str         = this->getString(_selected);
    auto            isPhonetics = _selected == PhoneticsENG || _selected == PhoneticsRUS;
    auto            skip        = false;
    auto&           word        = this->__word;
    u32             phVecIndex  = 0;
    std::vector<std::pair<Phonetics, int>> phoneticsVec;


    if ( _in.size() != str.size() )
        return "Diffrent word size!";

    // construct phonetics vec
    for ( auto& sym : word )
    {
        auto& ph = sym.phonetics;

        phoneticsVec.push_back({ph, phVecIndex});

        phVecIndex += sym.text.at(_selected).size();
    }
    phVecIndex = 0;


    if ( isPhonetics )
    {
        for ( int i = 0; i < _in.size();)
        {
            QString     currentSym;
            auto&       ph      = phoneticsVec.at(phVecIndex).first;
            auto&       wordSym = word.at(phVecIndex).text.at(_selected);
            auto        phSize  = word.at(phVecIndex).text.at(_selected).size();


            for ( int j = 0; j < phSize; j++ )
                currentSym += _in.at(i + j);

            // find out phonetics vec index
            if ( i == phoneticsVec.at(phVecIndex).second ) ++phVecIndex;

            if ( skip )
            {
                skip    = false;
                if ( phVecIndex > phoneticsVec.size() - 1 ) break;
                else i = phoneticsVec.at(phVecIndex).second;
                continue;
            }


            if ( ph == Phonetics::V )
            {
                // if next sym in word bounds
                if ( i + 1 < _in.size() )
                {
                    // if next sym is vowel
                    if ( phoneticsVec.at(phVecIndex).first == Phonetics::V )
                    {
                        QString         nextSym = _in.at(i + 1);
                        const QString&  sym_o   = Column1.at(4).text.at(_selected);


                        if ( this->__flags.useoi && currentSym == sym_o && nextSym != currentSym )
                        {
                            auto res = makeOI(currentSym, nextSym, wordSym, _selected);
                            out += res.first;

                            if ( res.second )
                            {
                                skip = true;
                                continue;
                            }
                        }
                        else if ( this->__flags.useDoubleVowelSign && (nextSym == currentSym || nextSym == DoubleVowelSign) )
                        {
                            out += pushSym(currentSym, wordSym);

                            if ( nextSym == DoubleVowelSign || nextSym == currentSym )
                                out += makeGreenHTML(nextSym);
                            else out += makeRedHTML(nextSym);

                            skip = true;
                            continue;
                        }
                        else out += pushSym(currentSym, wordSym);
                    }
                    else out += pushSym(currentSym, wordSym);
                }
                else out += pushSym(currentSym, wordSym);
            }
            else if ( ph == Phonetics::CV )
            {
                out += pushSym(currentSym, wordSym);
            }
            else if ( ph == Phonetics::N )
            {
                out += pushSym(currentSym, NN.text.at(_selected));
            }
            else if ( ph == Phonetics::SmallTSU )
            {
                auto nextSym = _in.at(i + 1);

                out += pushSym(currentSym, nextSym);
            }

            if ( phVecIndex > phoneticsVec.size() - 1 ) break;
            else i = phoneticsVec.at(phVecIndex).second;
        }
    }
    else
    {
        for ( int i = 0; i < _in.size(); i++ )
        {
            auto& sym = _in.at(i);

            if ( sym != str.at(i) )
            {
                out += makeRedHTML(sym);
            }
            else out += makeGreenHTML(sym);
        }
    }

    return out;
}
