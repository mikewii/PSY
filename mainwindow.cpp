#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Emotion.hpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    this->setWindowTitle("PSY");

    this->fillAllCBox();

    auto fontSizeCurrent = this->ui->generatedText->fontInfo().pointSize();
    this->ui->fontSizeJPN->setValue(fontSizeCurrent);

    this->settingsUi = new Settings(this);


    connect(this->settingsUi, SIGNAL(notifyOnError(QString)), this, SLOT(notify(QString)));
}

MainWindow::~MainWindow()
{
    delete this->settingsUi;
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

void MainWindow::notify(QString _text)
{
    this->ui->statusbar->showMessage(_text, 10);
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
    Japanese::generate( this->settingsUi->getSettingsJPN() );

    this->ui->comparedText->clear();
    this->ui->inputJPN->clear();

    auto chosenString = this->ui->cbox_displayTextJPN->currentIndex();
    this->ui->generatedText->setText(Japanese::getString(SymbolEnum(chosenString)));
}


void MainWindow::on_checkJPN_clicked()
{
    const auto& first   = this->ui->generatedText->toPlainText();
    const auto& second  = this->ui->inputJPN->text();

    if ( first.size() != second.size() )
    {
        this->ui->comparedText->setText("Word size is different!");
        this->notify("Японский: разный размер слова!");
        return;
    }

    auto selection  = this->ui->cbox_check_selection_JPN->currentIndex();
    auto out = Japanese::check(second, SymbolEnum(selection));

    this->ui->comparedText->setText(out);
    this->updateHTMLFontSize();
}


void MainWindow::on_cbox_displayTextJPN_currentIndexChanged(int index)
{
    this->ui->generatedText->setText(Japanese::getString(SymbolEnum(index)));
}


void MainWindow::on_settingsBtnJPN_clicked()
{
    this->settingsUi->show();
}


void MainWindow::on_fontSizeJPN_valueChanged(int arg1)
{
    auto currentGeneratedText   = this->ui->generatedText->toPlainText();

    this->ui->generatedText->setFontPointSize(arg1);
    this->ui->generatedText->setText(currentGeneratedText);

    this->updateHTMLFontSize();
}

