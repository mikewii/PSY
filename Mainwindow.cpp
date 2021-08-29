#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include "Journal/Emotion.hpp"
#include <QTime>

#include "Icon.hpp"

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
}

MainWindow::~MainWindow()
{
    delete this->uiSettings;
    delete ui;
}

void MainWindow::updateHTMLFontSize()
{
    QRegExp regex("[0-9]+pt");
    QString fontSize = QString::number(this->ui->fontSizeJPN->value()) + "pt";

    auto html = this->ui->comparedText->toHtml();

    html.replace(regex, fontSize);

    this->ui->comparedText->setHtml(html);
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
                "Запись добавлена успешно!";


        if ( res )
            ui->statusbar->showMessage(success);
        else
            this->notify("Ошибка при добавлении записи!");
    }
    else this->notify("Запись должна иметь описание!");
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

