#pragma once
#include <QWidget>
#include <QDialog>
#include <QFile>
#include "Settings.hpp"


namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT


public:
    explicit SettingsWindow( QWidget *parent = nullptr );
    ~SettingsWindow();

    Settings_s  getSettingsJPN( void ) const;
    void        saveSettings( void );
    bool        loadSettings( void );


signals:
    void notifySettings( QString _text, int _timeoutSec = 10 );


private slots:
    void on_settingsSave_clicked();

    void on_settingsLoad_clicked();

private:
    Ui::SettingsWindow  *ui;
    QFile               file;
    QString             __magic = "PSY0";
    Settings_s          __settings;

    void applySettings( void );
};
