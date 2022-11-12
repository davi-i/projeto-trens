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

    for (size_t i = 0; i < QUANT_TRAINS; i++) {
        auto x = labels[i]->geometry().x();
        auto y = labels[i]->geometry().y();
        trains[i] = new Train(i + 1, x, y);
    }

    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */

    for (size_t i = 0; i < QUANT_TRAINS; i++) {
        connect(trains[i], SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));
    }
}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    labels[id - 1]->setGeometry(x, y, 20, 20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Ao clicar, trens começam execução
 */
void MainWindow::on_pushButton_clicked()
{
    for (size_t i = 0; i < QUANT_TRAINS; i++) {
        trains[i]->start();
    }
}

/*
 * Ao clicar, trens param execução
 */
void MainWindow::on_pushButton_2_clicked()
{
    for (size_t i = 0; i < QUANT_TRAINS; i++) {
        trains[i]->terminate();
    }
}
