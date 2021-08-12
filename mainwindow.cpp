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

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addButton_clicked()
{
    auto&   tex = this->ui->textEditor;
    auto&   ui  = this->ui;

    if ( !tex->toPlainText().isEmpty() )
    {


        CFile::append( tex->toPlainText(),
                       {{
                           { EmoEnum::anger,    ui->angerCBox->currentIndex() },
                           { EmoEnum::fear,     ui->fearCBox->currentIndex() },
                           { EmoEnum::sadness,  ui->sadnessCBox->currentIndex() },
                           { EmoEnum::joy,      ui->joyCBox->currentIndex() },
                           { EmoEnum::love,     ui->loveCBox->currentIndex() }
                       }});
    }
}

void MainWindow::fillAllCBox()
{
    auto& angerCBox = this->ui->angerCBox;
    auto& fearCBox = this->ui->fearCBox;
    auto& sadnessCBox = this->ui->sadnessCBox;
    auto& joyCBox = this->ui->joyCBox;
    auto& loveCBox = this->ui->loveCBox;


    angerCBox->insertItems(0, EmoAnger);
    fearCBox->insertItems(0, EmoFear);
    sadnessCBox->insertItems(0, EmoSadness);
    joyCBox->insertItems(0, EmoJoy);
    loveCBox->insertItems(0, EmoLove);
}

