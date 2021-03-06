#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include "Journal/Emotion.hpp"
#include <QTime>
#include "Icon.hpp"
#include "Iconwindow.h"
#include <QColorDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    this->setWindowTitle("PSY");

    this->fillAllCBox();

    auto fontSizeCurrent = this->ui->generatedText->fontInfo().pointSize();
    this->ui->fontSizeJPN->setValue(fontSizeCurrent);

    this->uiSettings = new SettingsWindow(this);

    connect(this->uiSettings, SIGNAL(notifySettings(QString,int)), this, SLOT(notify(QString,int)));

    this->constructProbVec();
}

MainWindow::~MainWindow()
{
    delete this->uiSettings;
    delete ui;
}

void MainWindow::updateHTMLFontSize()
{
    QRegularExpression regex("[0-9]+pt");
    QString fontSize = QString::number(this->ui->fontSizeJPN->value()) + "pt";

    auto html = this->ui->comparedText->toHtml();

    html.replace(regex, fontSize);

    this->ui->comparedText->setHtml(html);
}

void MainWindow::constructProbVec( void )
{
    ProbItem element;


    probVec.reserve(10);


    element = {this->ui->widgetA, this->ui->labelA, this->ui->valueA};
    probVec.push_back(element);

    element = {this->ui->widgetB, this->ui->labelB, this->ui->valueB};
    probVec.push_back(element);

    element = {this->ui->widgetC, this->ui->labelC, this->ui->valueC};
    probVec.push_back(element);

    element = {this->ui->widgetD, this->ui->labelD, this->ui->valueD};
    probVec.push_back(element);

    element = {this->ui->widgetE, this->ui->labelE, this->ui->valueE};
    probVec.push_back(element);

    element = {this->ui->widgetF, this->ui->labelF, this->ui->valueF};
    probVec.push_back(element);

    element = {this->ui->widgetG, this->ui->labelG, this->ui->valueG};
    probVec.push_back(element);

    element = {this->ui->widgetH, this->ui->labelH, this->ui->valueH};
    probVec.push_back(element);

    element = {this->ui->widgetI, this->ui->labelI, this->ui->valueI};
    probVec.push_back(element);

    element = {this->ui->widgetJ, this->ui->labelJ, this->ui->valueJ};
    probVec.push_back(element);
}

void MainWindow::notify( QString _text, int _timeoutSec )
{
    this->ui->statusbar->showMessage(_text, 1000 * _timeoutSec);
}


void MainWindow::on_addButton_clicked()
{
    auto&   tex = this->ui->textEditor;
    auto&   ui  = this->ui;

    if ( !tex->toPlainText().isEmpty() )
    {
        auto date = QDate::currentDate().toString(Journal::fmt);
        auto time = QTime::currentTime().toString(Journal::fmt);

        const Journal::Emotion emo =
        {
            ui->angerCBox->currentIndex(),
            ui->fearCBox->currentIndex(),
            ui->sadnessCBox->currentIndex(),
            ui->joyCBox->currentIndex(),
            ui->loveCBox->currentIndex()
        };

        bool res = Journal::append( tex->toPlainText(), emo );

        QString success =
                date + Journal::space +
                time + Journal::space +
                Journal::divider + Journal::space +
                "???????????? ?????????????????? ??????????????!";


        if ( res )
            ui->statusbar->showMessage(success);
        else
            this->notify("???????????? ?????? ???????????????????? ????????????!");
    }
    else this->notify("???????????? ???????????? ?????????? ????????????????!");
}

void MainWindow::fillAllCBox()
{
    auto& angerCBox     = this->ui->angerCBox;
    auto& fearCBox      = this->ui->fearCBox;
    auto& sadnessCBox   = this->ui->sadnessCBox;
    auto& joyCBox       = this->ui->joyCBox;
    auto& loveCBox      = this->ui->loveCBox;


    angerCBox->insertItems(0, EmoAnger);
    fearCBox->insertItems(0, EmoFear);
    sadnessCBox->insertItems(0, EmoSadness);
    joyCBox->insertItems(0, EmoJoy);
    loveCBox->insertItems(0, EmoLove);
}


void MainWindow::on_generateJPN_clicked()
{
    Japanese::generate( this->uiSettings->getSettingsJPN() );

    this->ui->comparedText->clear();
    this->ui->inputJPN->clear();

    auto chosenString = this->ui->cbox_displayTextJPN->currentIndex();
    this->ui->generatedText->setText(Japanese::getString(SymbolEnum(chosenString)));
}


void MainWindow::on_checkJPN_clicked()
{
    const auto& word = this->ui->inputJPN->text();


    auto selection  = this->ui->cbox_check_selection_JPN->currentIndex();
    auto out        = Japanese::check(word, SymbolEnum(selection));

    this->ui->comparedText->setText(out);
    this->updateHTMLFontSize();
}


void MainWindow::on_cbox_displayTextJPN_currentIndexChanged(int index)
{
    auto str = Japanese::getString(SymbolEnum(index));

    if ( !str.isEmpty() )
        this->ui->generatedText->setText(str);
}


void MainWindow::on_settingsBtnJPN_clicked()
{
    this->uiSettings->show();
}


void MainWindow::on_fontSizeJPN_valueChanged(int arg1)
{
    auto currentGeneratedText   = this->ui->generatedText->toPlainText();

    this->ui->generatedText->setFontPointSize(arg1);
    this->ui->generatedText->setText(currentGeneratedText);

    this->updateHTMLFontSize();
}


void MainWindow::on_actionShow_triggered()
{
    Iconwindow icon;

    icon.exec();
}

void MainWindow::on_checkUntilTarget_toggled(bool checked)
{
    this->ui->cycleAmmount->setEnabled(!checked);
}


void MainWindow::on_actionColor_picker_triggered()
{
    QColorDialog diag;

    diag.exec();
}

