#include "Iconwindow.h"
#include "ui_Iconwindow.h"
#include "Icon.hpp"
#include <QFile>
#include <QImage>
#include <QDir>
#include "Utils.h"


Iconwindow::Iconwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Iconwindow)
{
    ui->setupUi(this);
    this->ui->pic->setAlignment(Qt::AlignCenter);

    this->showAppIcon();
}

Iconwindow::~Iconwindow()
{
    delete ui;
}

void Iconwindow::on_btn_generate_clicked()
{
    this->curIsAppIcon = false;
    auto width  = this->ui->spin_width->value();
    auto height = this->ui->spin_height->value();

    this->ui->pic->setPixmap(Icon(width, height, this->ui->check_text->isChecked()).pixmap(width, height));
}


void Iconwindow::on_btn_save_clicked()
{
    QFile file(QDir::homePath() + QDir::separator() + "psyIcon.png");

    file.open(QIODevice::WriteOnly);

#if QT_VERSION >= QT_VERSION_CHECK(5,15,0)
    const auto&  pixmap = this->ui->pic->pixmap(Qt::ReturnByValue);

    if ( !pixmap.isNull() )
        pixmap.save(&file, "PNG");
#else
    const auto&  pixmap = this->ui->pic->pixmap();

    if ( pixmap )
        pixmap->save(&file, "PNG");
#endif

    file.close();

#ifdef USE_SVG
    QFile filesvg(QDir::homePath() + QDir::separator() + "psyIcon.svg");

    filesvg.open(QIODevice::WriteOnly);

    QByteArray* data = this->curIsAppIcon ? Utils::getAppIconBytesArray() : Utils::getBytesArray();

    filesvg.write(*data);

    filesvg.close();
#endif
}

void Iconwindow::showAppIcon()
{
    this->curIsAppIcon = true;
    const auto&    sizes   = this->windowIcon().availableSizes();
    const auto&    appIcon = this->windowIcon().pixmap(sizes.at(0));

    this->ui->pic->setPixmap(appIcon);
}


void Iconwindow::on_btn_appIcon_clicked()
{
    this->showAppIcon();
}

