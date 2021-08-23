#include "settings.h"
#include "ui_settings.h"
#include <QSettings>
#include <QDir>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowTitle("PSY::Settings");

    this->file.setFileName(QDir::homePath() + QDir::separator() + ".psyJPNSettings");

    this->loadSettings();
}

Settings::~Settings()
{
    delete ui;
}

Japanese::Flags Settings::getSettingsJPN() const
{
    Japanese::Flags flags;
    auto& ui = this->ui;

    flags.wordLength            = ui->wordLengthJPN->value();
    flags.wordLengthLimit       = ui->wordLengthJPN->maximum();
    flags.wordLengthRandom      = ui->randomWordLengthJPN->isChecked();
    flags.preventTriplets       = ui->check_preventTripletsJPN->isChecked();

    flags.col2_k                = ui->check_col2_k->isChecked();
    flags.col2_g                = ui->check_col2_g->isChecked();
    flags.col3_s                = ui->check_col3_s->isChecked();
    flags.col3_z                = ui->check_col3_z->isChecked();
    flags.col4_t                = ui->check_col4_t->isChecked();
    flags.col4_d                = ui->check_col4_d->isChecked();
    flags.col5_n                = ui->check_col5_n->isChecked();
    flags.col6_h                = ui->check_col6_h->isChecked();
    flags.col6_b                = ui->check_col6_b->isChecked();
    flags.col6_p                = ui->check_col6_p->isChecked();

    flags.longConsonant         = ui->check_longConsonant->isChecked();
    flags.nn                    = ui->check_nn->isChecked();

    flags.useDoubleVowelSign        = ui->check_doubleVowelsPho->isChecked();
    flags.useoi                 = ui->check_oiPho->isChecked();

    if ( flags.col2_k ||
         flags.col2_g ||
         flags.col3_s ||
         flags.col3_z ||
         flags.col4_t ||
         flags.col4_d ||
         flags.col5_n ||
         flags.col6_h ||
         flags.col6_b ||
         flags.col6_p )
        flags.multipleColumn = true;

    return flags;
}

void Settings::saveSettings()
{
    if ( this->file.open(QFile::WriteOnly) )
    {
        QString header;
        QByteArray data;
        Japanese::Flags flags = Settings::getSettingsJPN();


        header += this->__magic + __timestamp;

        data.reserve(sizeof(u32) + sizeof(Japanese::Flags));

        for ( u32 i = 0; i < sizeof(u32); i++ ) // padding
            data.append(255);

        for ( u32 i = 0; i < sizeof(Japanese::Flags); i++ ) // flags
            data.append(flags.raw_byte[i]);

        this->file.write(header.toUtf8());
        this->file.write(data);

        emit this->notifySettings("Settings::Save successfull!");

        this->file.close();
    }
    else emit this->notifySettings("Settings::Error trying to save file!");
}

bool Settings::loadSettings()
{
    bool res = false;


    if ( this->file.open(QFile::ReadOnly) )
    {
        // magic
        auto magic = this->file.read(this->__magic.size());
        if ( this->__magic.compare(magic, Qt::CaseSensitive) != 0 )
        {
            this->file.close();
            return false;
        }

        // timestamp
        this->file.seek(this->__magic.size());
        auto timestamp = this->file.read(__timestamp.size());
        if ( __timestamp.compare(timestamp, Qt::CaseSensitive) != 0 )
        {
            this->file.close();
            return false;
        }

        // reading flags
        this->file.seek(this->__magic.size() + __timestamp.size() + sizeof(u32));
        this->file.read(this->__flags.raw_byte, sizeof(Japanese::Flags));

        this->file.close();
        res = true;
    }
    else emit this->notifySettings("Settings::Error trying to load file!");

    if ( res )
        this->applySettings();

    return res;
}

void Settings::on_settingsSave_clicked()
{
    this->saveSettings();
}


void Settings::on_settingsLoad_clicked()
{
    auto res = this->loadSettings();
    if ( !res )
    {
        emit this->notifySettings("Settings::Failed to load settings file, overwriting!");
        this->saveSettings();
    }
}

void Settings::applySettings()
{
    Japanese::Flags&    f = this->__flags;
    auto&               ui = this->ui;

    ui->wordLengthJPN->setValue(f.wordLength);
    ui->wordLengthJPN->setMaximum(f.wordLengthLimit);
    ui->randomWordLengthJPN->setChecked(f.wordLengthRandom);
    ui->check_preventTripletsJPN->setChecked(f.preventTriplets);

    ui->check_col2_k->setChecked(f.col2_k);
    ui->check_col2_g->setChecked(f.col2_g);
    ui->check_col3_s->setChecked(f.col3_s);
    ui->check_col3_z->setChecked(f.col3_z);
    ui->check_col4_t->setChecked(f.col4_t);
    ui->check_col4_d->setChecked(f.col4_d);
    ui->check_col5_n->setChecked(f.col5_n);
    ui->check_col6_h->setChecked(f.col6_h);
    ui->check_col6_b->setChecked(f.col6_b);
    ui->check_col6_p->setChecked(f.col6_p);

    ui->check_longConsonant->setChecked(f.longConsonant);
    ui->check_nn->setChecked(f.nn);

    ui->check_doubleVowelsPho->setChecked(f.useDoubleVowelSign);
    ui->check_oiPho->setChecked(f.useoi);
}

