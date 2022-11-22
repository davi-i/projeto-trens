#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    labels[0] = ui->label_trem1;
    labels[1] = ui->label_trem2;
    labels[2] = ui->label_trem3;
    labels[3] = ui->label_trem4;
    labels[4] = ui->label_trem5;

    int speed[5] = {
        ui->horizontalSlider->value(),
        ui->horizontalSlider_2->value(),
        ui->horizontalSlider_3->value(),
        ui->horizontalSlider_4->value(),
        ui->horizontalSlider_5->value(),
    };

    for (size_t i = 0; i < QUANT_TRAINS; i++) {
        auto x = labels[i]->geometry().x();
        auto y = labels[i]->geometry().y();
        trains[i] = new Train(i + 1, x, y, speed[i]);
    }

    for (size_t i = 0; i < QUANT_TRAINS; i++)
        connect(trains[i], SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));
}

void MainWindow::updateInterface(int id, int x, int y){
    labels[id - 1]->setGeometry(x, y, 20, 20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    std::cout << "chaged speed of T1 to " << value << '\n';
    ui->label->setText(QString::number(value));
    trains[0]->setSpeed(value);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    std::cout << "chaged speed of T2 to " << value << '\n';
    ui->label_2->setText(QString::number(value));
    trains[1]->setSpeed(value);
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    std::cout << "chaged speed of T3 to " << value << '\n';
    ui->label_3->setText(QString::number(value));
    trains[2]->setSpeed(value);
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    std::cout << "chaged speed of T4 to " << value << '\n';
    ui->label_4->setText(QString::number(value));
    trains[3]->setSpeed(value);
}

void MainWindow::on_horizontalSlider_5_valueChanged(int value)
{
    std::cout << "chaged speed of T5 to " << value << '\n';
    ui->label_5->setText(QString::number(value));
    trains[4]->setSpeed(value);
}
