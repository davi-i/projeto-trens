#include "train.h"
#include <QtCore>

//Construtor
Train::Train(int ID, int x, int y){
    this->ID = ID;
    this->curr_pos.x = this->start_pos.x = x;
    this->curr_pos.y = this->start_pos.y = y;
    speed = 100;
}

//Função a ser executada após executar trem->START
void Train::run(){
    while (true) {
        if (curr_pos.y == start_pos.y && curr_pos.x < start_pos.x + 250) {
            curr_pos.x += 10;
        } else if (curr_pos.x == start_pos.x + 250 && curr_pos.y < start_pos.y + 120) {
            curr_pos.y += 10;
        } else if (curr_pos.x > start_pos.x - 20 && curr_pos.y == start_pos.y + 120) {
            curr_pos.x -= 10;
        } else {
            curr_pos.y -= 10;
        }
        emit updateGUI(ID, curr_pos.x, curr_pos.y);    //Emite um sinal
        msleep(speed);
    }
}




