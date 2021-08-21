#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "file.h"
#include "japanese.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public CFile, public Japanese
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();

    void on_generateJPN_clicked();

    void on_checkJPN_clicked();

    void on_cbox_displayTextJPN_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    void fillAllCBox( void );
};
#endif // MAINWINDOW_H
