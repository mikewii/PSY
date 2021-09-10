#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include "Utils.h"


static inline const QString getSymbol( const uint32_t value )
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


static uint32_t    getTotal( const std::vector<uint32_t>& _vec, const uint32_t _selection )
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
        outText += QString::asprintf("Cost to reach %s = %d\n",
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
    auto                        total   = 0;
    const auto&                 value   = this->ui->normalizeValue->value();
    const auto&                 valueA  = this->ui->valueA->value();
    auto                        div     = this->ui->vectorSize->value();

    div -= 1; // dont count first one
    vec.reserve(div);

    // guards
    if ( div == 1 )
    {
        probVec.at(1).spinox->setValue(value - valueA);
        return;
    }
    if ( (value - valueA - div) <= div )
        return;
    // /guards


    auto    rLimit = value - 1 - div - valueA;


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
