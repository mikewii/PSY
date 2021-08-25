#include "CSettingswindow.h"
#include "ui_CSettingswindow.h"
#include <QSettings>
#include <QDir>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("PSY::Settings");

    this->file.setFileName(QDir::homePath() + QDir::separator() + ".psyJPNSettings");

    this->loadSettings();
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

Settings_s SettingsWindow::getSettingsJPN() const
{
    Settings_s      settings;
    auto&           ui = this->ui;


    settings.wordLength             = ui->wordLengthJPN->value();
    settings.wordLengthLimit        = ui->wordLengthJPN->maximum();
    settings.wordLengthRandom       = ui->randomWordLengthJPN->isChecked();
    settings.preventTriplets        = ui->check_preventTripletsJPN->isChecked();
    settings.preventDiDu            = ui->check_preventDiDuJPN->isChecked();

    settings.col2_k                 = ui->check_col2_k->isChecked();
    settings.col2_g                 = ui->check_col2_g->isChecked();
    settings.col3_s                 = ui->check_col3_s->isChecked();
    settings.col3_z                 = ui->check_col3_z->isChecked();
    settings.col4_t                 = ui->check_col4_t->isChecked();
    settings.col4_d                 = ui->check_col4_d->isChecked();
    settings.col5_n                 = ui->check_col5_n->isChecked();
    settings.col6_h                 = ui->check_col6_h->isChecked();
    settings.col6_b                 = ui->check_col6_b->isChecked();
    settings.col6_p                 = ui->check_col6_p->isChecked();

    settings.longConsonant          = ui->check_longConsonant->isChecked();
    settings.nn                     = ui->check_nn->isChecked();

    settings.useDoubleVowelSign     = ui->check_doubleVowelsPho->isChecked();
    settings.useoi                  = ui->check_oiPho->isChecked();

    if ( settings.col2_k ||
         settings.col2_g ||
         settings.col3_s ||
         settings.col3_z ||
         settings.col4_t ||
         settings.col4_d ||
         settings.col5_n ||
         settings.col6_h ||
         settings.col6_b ||
         settings.col6_p )
        settings.multipleColumn = true;

    return settings;
}

void SettingsWindow::saveSettings()
{
    if ( this->file.open(QFile::WriteOnly) )
    {
        QString     header;
        QByteArray  data;
        Settings_s  settings = this->getSettingsJPN();


        header += this->__magic + settingsTimestamp;

        data.reserve(sizeof(u32) + sizeof(Settings_s));

        for ( u32 i = 0; i < sizeof(u32); i++ ) // padding
            data.append(255);

        for ( u32 i = 0; i < sizeof(Settings_s); i++ ) // flags
            data.append(settings.raw_byte[i]);

        this->file.write(header.toUtf8());
        this->file.write(data);

        emit this->notifySettings("Settings::Save successfull!");

        this->file.close();
    }
    else emit this->notifySettings("Settings::Error trying to save file!");
}

bool SettingsWindow::loadSettings()
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
        auto fileTimestamp = this->file.read(settingsTimestamp.size());
        if ( settingsTimestamp.compare(fileTimestamp, Qt::CaseSensitive) != 0 )
        {
            this->file.close();
            return false;
        }

        // reading flags
        this->file.seek(this->__magic.size() + settingsTimestamp.size() + sizeof(u32));
        this->file.read(this->__settings.raw_byte, sizeof(Settings_s));

        this->file.close();
        res = true;
    }
    else emit this->notifySettings("Settings::Error trying to load file!");

    if ( res )
        this->applySettings();

    return res;
}

void SettingsWindow::on_settingsSave_clicked()
{
    this->saveSettings();
}


void SettingsWindow::on_settingsLoad_clicked()
{
    auto res = this->loadSettings();
    if ( !res )
    {
        emit this->notifySettings("Settings::Failed to load settings file, overwriting!");
        this->saveSettings();
    }
}

void SettingsWindow::applySettings()
{
    Settings_s&     s = this->__settings;
    auto&           ui = this->ui;


    ui->wordLengthJPN->setValue(s.wordLength);
    ui->wordLengthJPN->setMaximum(s.wordLengthLimit);
    ui->randomWordLengthJPN->setChecked(s.wordLengthRandom);
    ui->check_preventTripletsJPN->setChecked(s.preventTriplets);
    ui->check_preventDiDuJPN->setChecked(s.preventDiDu);

    ui->check_col2_k->setChecked(s.col2_k);
    ui->check_col2_g->setChecked(s.col2_g);
    ui->check_col3_s->setChecked(s.col3_s);
    ui->check_col3_z->setChecked(s.col3_z);
    ui->check_col4_t->setChecked(s.col4_t);
    ui->check_col4_d->setChecked(s.col4_d);
    ui->check_col5_n->setChecked(s.col5_n);
    ui->check_col6_h->setChecked(s.col6_h);
    ui->check_col6_b->setChecked(s.col6_b);
    ui->check_col6_p->setChecked(s.col6_p);

    ui->check_longConsonant->setChecked(s.longConsonant);
    ui->check_nn->setChecked(s.nn);

    ui->check_doubleVowelsPho->setChecked(s.useDoubleVowelSign);
    ui->check_oiPho->setChecked(s.useoi);
}
