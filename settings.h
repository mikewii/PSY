#pragma once
#include <QWidget>
#include <QDialog>
#include <QFile>
#include "Japanese.hpp"


namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT


public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    Japanese::Flags getSettingsJPN( void ) const;
    void saveSettings( void );
    bool loadSettings( void );


signals:
    void notifySettings( QString _text);


private slots:
    void on_settingsSave_clicked();

    void on_settingsLoad_clicked();

private:
    Ui::Settings    *ui;
    QFile           file;
    QString         __magic       = "PSY0";
    QString         __timestamp   = __TIMESTAMP__;
    Japanese::Flags __flags;

    void applySettings( void );
};
