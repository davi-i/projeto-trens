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
//        void enterRegion(int,int);
//        void exitRegion(int);

    private slots:
        void on_horizontalSlider_valueChanged(int value);
        void on_horizontalSlider_2_valueChanged(int value);
        void on_horizontalSlider_3_valueChanged(int value);
        void on_horizontalSlider_4_valueChanged(int value);
        void on_horizontalSlider_5_valueChanged(int value);

private:
        Ui::MainWindow *ui;

        Train* trains[QUANT_TRAINS];
        QLabel* labels[QUANT_TRAINS];
};

#endif // MAINWINDOW_H
