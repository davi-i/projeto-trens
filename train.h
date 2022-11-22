#ifndef TRAIN_H
#define TRAIN_H

#include <QThread>
#include <iostream>

struct Position {
    int x;
    int y;
};

class Train: public QThread{
 Q_OBJECT
public:
    Train(int,int,int,int);
    void run();
    void setSpeed(int);

signals:
    void updateGUI(int,int,int);

private:
   Position curr_pos;
   Position start_pos;
   int ID;
   int speed;
};

#endif // TRAIN_H
