#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "train.h"

const size_t QUANT_TRAINS = 5;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();


    public slots:
        void updateInterface(int,int,int);

    private slots:
        void on_pushButton_clicked();
        void on_pushButton_2_clicked();

    private:
        Ui::MainWindow *ui;

        //Cria os objetos TREM's
        Train* trains[QUANT_TRAINS];
        QLabel* labels[QUANT_TRAINS];
};

#endif // MAINWINDOW_H
