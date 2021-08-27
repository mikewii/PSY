#pragma once
#include <QString>
#include "CWord.hpp"
#include "CGrammar.hpp"
#include "CPhonetics.hpp"
#include "CCheck.hpp"


class Japanese : public Word, public Grammar, public PhoneticsGenerator, public Check
{
public:
    void    generate( const Settings_s _settings );
    QString check( const QString& _in, const SymbolEnum _selected );

    QString getString( SymbolEnum _selected ) const;

private:
    QStringList __strings;
};


