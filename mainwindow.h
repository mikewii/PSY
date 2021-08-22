#pragma once
#include <QMainWindow>
#include "Journal.hpp"
#include "Japanese.hpp"
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public Journal, public Japanese
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateHTMLFontSize( void );

private slots:
    void notify( QString _text );
    void on_addButton_clicked();

    void on_generateJPN_clicked();

    void on_checkJPN_clicked();

    void on_cbox_displayTextJPN_currentIndexChanged(int index);

    void on_settingsBtnJPN_clicked();

    void on_fontSizeJPN_valueChanged(int arg1);

private:
    Ui::MainWindow  *ui;
    Settings        *settingsUi;

    void fillAllCBox( void );
};
