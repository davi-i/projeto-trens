#include "train.h"
#include <QtCore>

#include <iostream>
#include <QMutex>

QMutex mutex;
bool regions[7] = {};

Train::Train(int ID, int x, int y){
    this->ID = ID;
    this->curr_pos.x = this->start_pos.x = x;
    this->curr_pos.y = this->start_pos.y = y;
    speed = 50;
}

void Train::run(){
    while (true) {
        if ( curr_pos.x < start_pos.x + 250 && curr_pos.y == start_pos.y ) {
            if (curr_pos.x == start_pos.x + 230) {
                if (ID == 1) {
                    mutex.lock();
                    if (!regions[0] && !regions[2]) {
                        regions[0] = true;
                        regions[2] = true;
                        curr_pos.x += 5;
                    }
                    mutex.unlock();
                } else if (ID == 2) {
                    mutex.lock();
                    if (!regions[0] && !regions[1] && !regions[3] && !regions[4]) {
                        regions[0] = true;
                        regions[1] = true;
                        regions[3] = true;
                        regions[4] = true;
                        curr_pos.x += 5;
                    }
                    mutex.unlock();
                } else {
                    curr_pos.x += 5;
                }
            } else {
                if (curr_pos.x == start_pos.x) {
                    if (ID == 2) {
                        mutex.lock();
                        regions[0] = false;
                        mutex.unlock();
                    } else if (ID == 3) {
                        mutex.lock();
                        regions[1] = false;
                        mutex.unlock();
                    }  else if (ID == 5) {
                        mutex.lock();
                        regions[6] = false;
                        mutex.unlock();
                    }
                } else if (curr_pos.x == start_pos.x + 135) {
                    if (ID == 4) {
                        mutex.lock();
                        regions[2] = false;
                        mutex.unlock();
                    } else if (ID == 5) {
                        mutex.lock();
                        regions[4] = false;
                        mutex.unlock();
                    }
                }
                curr_pos.x += 5;
            }
        } else if ( curr_pos.x == start_pos.x + 250 && curr_pos.y < start_pos.y + 120 ) {
            if (curr_pos.y == start_pos.y + 20) {
                if (ID == 4) {
                    mutex.lock();
                    regions[3] = false;
                    mutex.unlock();
                } else if (ID == 5) {
                    mutex.lock();
                    regions[5] = false;
                    mutex.unlock();
                }
            }
            curr_pos.y += 5;
        } else if ( curr_pos.x > start_pos.x - 20 && curr_pos.y == start_pos.y + 120 ) {
            if (curr_pos.x == start_pos.x + 135) {
                if (ID == 3) {
                    mutex.lock();
                    if (!regions[1] && !regions[5]) {
                        regions[1] = true;
                        regions[5] = true;
                        curr_pos.x -= 5;
                    }
                    mutex.unlock();
                } else {
                    curr_pos.x -= 5;
                }
            } else if (curr_pos.x == start_pos.x) {
                if (ID == 5) {
                    mutex.lock();
                    if (!regions[4] && !regions[5] && !regions[6]) {
                        regions[4] = true;
                        regions[5] = true;
                        regions[6] = true;
                        curr_pos.x -= 5;
                    }
                    mutex.unlock();
                } else {
                    curr_pos.x -= 5;
                }
            } else {
                if (curr_pos.x == start_pos.x + 230) {
                    if (ID == 1) {
                        mutex.lock();
                        regions[0] = false;
                        mutex.unlock();
                    } else if (ID == 2) {
                        mutex.lock();
                        regions[1] = false;
                        mutex.unlock();
                    } else if (ID == 4) {
                        mutex.lock();
                        regions[6] = false;
                        mutex.unlock();
                    }
                } else if (curr_pos.x == start_pos.x + 95) {
                    if (ID == 1) {
                        mutex.lock();
                        regions[2] = false;
                        mutex.unlock();
                    } else if (ID == 2) {
                        mutex.lock();
                        regions[4] = false;
                        mutex.unlock();
                    }
                }
                curr_pos.x -= 5;
            }
        } else {
            if (curr_pos.y == start_pos.y + 20) {
                if (ID == 4) {
                    mutex.lock();
                    if (!regions[2] && !regions[3] && !regions[6]) {
                        regions[2] = true;
                        regions[3] = true;
                        regions[6] = true;
                        curr_pos.y -= 5;
                    }
                    mutex.unlock();
                } else {
                    curr_pos.y -= 5;
                }
            } else {
                if (curr_pos.y == start_pos.y + 100) {
                    if (ID == 2) {
                        mutex.lock();
                        regions[3] = false;
                        mutex.unlock();
                    } else if (ID == 3) {
                        mutex.lock();
                        regions[5] = false;
                        mutex.unlock();
                    }
                }
                curr_pos.y -= 5;
            }
        }
        emit updateGUI(ID, curr_pos.x, curr_pos.y);
        msleep(speed);
    }
}

void Train::setSpeed( int speed ) {
    this->speed = 200 - speed;
    if (speed == 0)
        this->terminate();
    else if (!this->isRunning())
        this->start();
}
