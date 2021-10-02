#pragma once
#include <QMainWindow>
#include "Journal/Journal.hpp"
#include "Japanese/Japanese.hpp"
#include "Settingswindow.h"
#include <QLabel>
#include <QSpinBox>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public Journal, public Japanese
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void    updateHTMLFontSize( void );
    void    constructProbVec( void );

private slots:
    void notify( QString _text, int _timeoutSec = 10 );
    void on_addButton_clicked();

    void on_generateJPN_clicked();

    void on_checkJPN_clicked();

    void on_cbox_displayTextJPN_currentIndexChanged(int index);

    void on_settingsBtnJPN_clicked();

    void on_fontSizeJPN_valueChanged(int arg1);

    void on_actionShow_triggered();

    void on_probabilityRun_clicked();

    void on_vectorSize_valueChanged(int arg1);

    void on_normalizeButton_clicked();

    void on_checkUntilTarget_toggled(bool checked);

    void on_actionColor_picker_triggered();

private:
    Ui::MainWindow  *ui;
    SettingsWindow  *uiSettings;

    struct ProbItem {
        QWidget*    widget;
        QLabel*     label;
        QSpinBox*   spinox;
    };

    std::vector<ProbItem>  probVec;

    void fillAllCBox( void );
};
