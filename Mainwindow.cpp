#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include "Journal/Emotion.hpp"
#include <QTime>
#include "Icon.hpp"
#include "Iconwindow.h"
#include "Probability.hpp"



struct ProbItem {
    QWidget*    widget;
    QLabel*     label;
    QSpinBox*   spinox;
};

static std::vector<ProbItem>  probVec;


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
    QRegExp regex("[0-9]+pt");
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


void MainWindow::on_actionShow_triggered()
{
    Iconwindow* i = new Iconwindow(this);

    i->exec();

    delete i;
}


const QString getSymbol( const uint32_t value )
{
    switch(value)
    {
    default:
    case 0: return "A";
    case 1: return "B";
    case 2: return "C";
    case 3: return "D";
    case 4: return "E";
    case 5: return "F";
    case 6: return "G";
    case 7: return "H";
    case 8: return "I";
    case 9: return "J";
    }
}


uint32_t    getTotal( const std::vector<uint32_t>& _vec, const uint32_t _selection )
{
    uint32_t total = 0;

    for ( const auto& value : _vec )
        if ( value == _selection ) ++total;

    return total;
}


void MainWindow::on_probabilityRun_clicked()
{
    QString                 outText;
    std::vector<uint32_t>   valuesVec;
    std::vector<uint32_t>   resultVec;
    const auto&             vecSize = this->ui->vectorSize->value();
    const auto&             cycleAmmount = this->ui->cycleAmmount->value();
    const auto&             costPerCycle = this->ui->cycleCost->value();
    const auto&             textOutput = this->ui->textOutputProb;
    const auto&             untilTarget = this->ui->checkUntilTarget->isChecked();
    uint32_t                target = this->ui->target->currentIndex();
    uint32_t                totalCost = 0;

    // fill values vector
    for ( auto i = 0; i < vecSize; i++ )
        valuesVec.push_back(probVec.at(i).spinox->value());


    if ( untilTarget )
    {
        if ( probVec.at(target).spinox->value() == 0 )
        {
            textOutput->setText("Target must not be 0!");
            return;
        }


        for (;;)
        {
            auto res = Utils::getRandomChance(valuesVec);

            totalCost += costPerCycle;
            resultVec.push_back(res);

            if ( res == target ) break;
        }
    }
    else
    {
        for ( auto i = 0; i < cycleAmmount; i++ )
        {
            auto res = Utils::getRandomChance(valuesVec);

            resultVec.push_back(res);
        }
    }


    for ( uint32_t i = 0; i < valuesVec.size(); i++ )
    {
        QString text = QString::asprintf("Total %s = %d\n",
                        getSymbol(i).toStdString().c_str(), getTotal(resultVec, i));

        outText += text;
    }

    if ( untilTarget )
        outText += QString::asprintf("Cost to reash %s = %d\n",
                        getSymbol(target).toStdString().c_str(), totalCost);

    textOutput->setText(outText);
}


void MainWindow::on_vectorSize_valueChanged( int arg1 )
{
    static const QString    enabled = "background-color: rgb(0, 70, 0);";
    const auto&             applyDefault = this->ui->checkApplyDefault->isChecked();
    const auto&             defaultValue = this->ui->defaultValue->value();



    for ( auto i = 0; i < arg1; i++ )
    {
        auto* widget  = probVec.at(i).widget;
        auto* label   = probVec.at(i).label;
        auto* spinbox = probVec.at(i).spinox;

        // dont apply to A|B
        if ( i > 1 && applyDefault ) spinbox->setValue(defaultValue);

        if ( i > 1 )
        {
            widget->setStyleSheet(enabled);

            spinbox->setEnabled(true);
            label->setEnabled(true);
        }
    }

    // reverse disable widgets
    for ( auto i = 9; i >= arg1; i-- )
    {
        auto* widget  = probVec.at(i).widget;
        auto* label   = probVec.at(i).label;
        auto* spinbox = probVec.at(i).spinox;

        label->setEnabled(false);
        spinbox->setEnabled(false);

        widget->setStyleSheet("");
    }


    // target combobox | cant be bothered
    this->ui->target->clear();
    for ( auto i = 0; i < arg1; i++ )
    {
        this->ui->target->addItem(getSymbol(i));
    }
}


void MainWindow::on_normalizeButton_clicked()
{
    std::vector<uint32_t>       vec;
    auto                        total = 0;
    const auto&                 value   = this->ui->normalizeValue->value();
    const auto&                 valueA  = this->ui->valueA->value();
    auto                        div     = this->ui->vectorSize->value();

    div -= 1; // dont count first one

    if ( div == 1 )
    {
        probVec.at(1).spinox->setValue(value - valueA);
        return;
    }

    if ( (value - valueA - div) <= div )
        return;


    auto    rLimit = value - 1 - div - valueA;


    vec.reserve(div);

    for ( auto i = 0; i < div - 1; i++ )
    {
        auto num = Utils::getRandom(1, rLimit);

        rLimit -= num - 1;

        vec.push_back(num);
    }

    // sum all nums
    for ( const auto& num : vec )
        total += num;

    // sum will be less that value, no check needed
    vec.push_back(value - valueA - total);

    for ( auto i = 1; i <= div; i++ )
        probVec.at(i).spinox->setValue(vec.at(i - 1));
}


void MainWindow::on_checkUntilA_toggled(bool checked)
{
    this->ui->cycleAmmount->setEnabled(!checked);
}

