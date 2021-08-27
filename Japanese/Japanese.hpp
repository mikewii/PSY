#pragma once
#include <QString>
#include "Japanese/Word.hpp"
#include "Japanese/Grammar.hpp"
#include "Japanese/Phonetics.hpp"
#include "Japanese/Check.hpp"


class Japanese : virtual public Word, public Grammar, public PhoneticsGenerator, public Check
{
public:
    void        generate( const Settings_s _settings );
    QString     check( const QString& _in, const SymbolEnum _selected );

    QString     getString( const SymbolEnum _selected ) const;

private:
    QStringList     __strings;

    QStringList&    getStringList( void ) { return this->__strings; }
};


