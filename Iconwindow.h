#pragma once
#include <QDialog>

namespace Ui {
class Iconwindow;
}

class Iconwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Iconwindow(QWidget *parent = nullptr);
    ~Iconwindow();

private slots:
    void on_btn_generate_clicked();

    void on_btn_save_clicked();

    void on_btn_appIcon_clicked();

private:
    Ui::Iconwindow *ui;

    void showAppIcon( void );
};
