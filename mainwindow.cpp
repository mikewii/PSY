#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Emotion.hpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , CFile()
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    this->setWindowTitle("PSY");

    this->fillAllCBox();
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::on_addButton_clicked()
{
    auto&   tex = this->ui->textEditor;
    auto&   ui  = this->ui;

    if ( !tex->toPlainText().isEmpty() )
    {
        auto date = QDate::currentDate().toString(CFile::fmt);
        auto time = QTime::currentTime().toString(CFile::fmt);

        bool res = CFile::append(
                    tex->toPlainText(),
                    ui->angerCBox->currentIndex(),
                    ui->fearCBox->currentIndex(),
                    ui->sadnessCBox->currentIndex(),
                    ui->joyCBox->currentIndex(),
                    ui->loveCBox->currentIndex());

        QString success =
                date + CFile::space +
                time + CFile::space +
                CFile::divider + CFile::space +
                "Запись добавлена успешно!";


        if ( res )
            ui->statusbar->showMessage(success);
        else
            ui->statusbar->showMessage("Ошибка при добавлении записи!");
    }
    else ui->statusbar->showMessage("Запись должна иметь описание!");
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
    Japanese::Flags flags;

    flags.maxLength         = this->ui->generateMaxSymbolsJPN->maximum();
    flags.maxSymbolsRandom  = this->ui->generateMaxSymbolsRandomJPN->isChecked();
    flags.preventTriplets   = this->ui->check_triplets->isChecked();
    flags.longConsonants    = this->ui->check_longConsonants->isChecked();
    flags.nn                = this->ui->check_nn->isChecked();

    flags.col2_k = this->ui->check_col2_k->isChecked();
    flags.col2_g = this->ui->check_col2_g->isChecked();
    flags.col3_s = this->ui->check_col3_s->isChecked();
    flags.col3_z = this->ui->check_col3_z->isChecked();
    flags.col4_t = this->ui->check_col4_t->isChecked();
    flags.col4_d = this->ui->check_col4_d->isChecked();
    flags.col5_n = this->ui->check_col5_n->isChecked();
    flags.col6_h = this->ui->check_col6_h->isChecked();
    flags.col6_b = this->ui->check_col6_b->isChecked();
    flags.col6_p = this->ui->check_col6_p->isChecked();


    Japanese::generate( flags, this->ui->generateMaxSymbolsJPN->value() );

    this->ui->comparedText->clear();

    auto chosenString = this->ui->cbox_displayTextJPN->currentIndex();
    this->ui->generatedText->setText(Japanese::getString(SymbolEnum(chosenString)));
}


void MainWindow::on_checkJPN_clicked()
{
    const auto& first   = this->ui->generatedText->toPlainText();
    const auto& second  = this->ui->inputJPN->text();

    if ( first.size() != second.size() )
    {
        this->ui->statusbar->showMessage("Японский: разный размер слова!");
        return;
    }

    auto selection = this->ui->cbox_check_selection_JPN->currentIndex();
    auto out = Japanese::check(second, SymbolEnum(selection));

    this->ui->comparedText->setText(out);
}


void MainWindow::on_cbox_displayTextJPN_currentIndexChanged(int index)
{
//    auto chosenString = this->ui->cbox_displayTextJPN->currentIndex();
    this->ui->generatedText->setText(Japanese::getString(SymbolEnum(index)));
}

