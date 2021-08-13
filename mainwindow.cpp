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

