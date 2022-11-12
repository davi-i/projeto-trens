#ifndef TRAIN_H
#define TRAIN_H

#include <QThread>

struct Position {
    int x;
    int y;
};

/*
 * Classe Trem herda QThread
 * Classe Trem passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar a função RUN.
 * Para parar a execução da função RUN da thread, basta executar a função TERMINATE.
 *
*/
class Train: public QThread{
 Q_OBJECT
public:
    Train(int,int,int);  //construtor
    void run();         //função a ser executada pela thread


//Cria um sinal
signals:
    void updateGUI(int,int,int);

private:
   Position curr_pos;
   Position start_pos;
   int ID;          //ID do trem
   int speed;  //Velocidade. É o tempo de dormir em milisegundos entre a mudança de posição do trem
};

#endif // TRAIN_H
