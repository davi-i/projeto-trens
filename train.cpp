#include "train.h"
#include <array>
#include <iostream>

#include <QtCore>
#include <QMutex>

QMutex mutex;
bool regions[7] = {
    false, false, true, false, true, false, false
};

Train::Train(int ID, int x, int y){
    this->ID = ID;
    this->curr_pos.x = this->start_pos.x = x;
    this->curr_pos.y = this->start_pos.y = y;
}

template <unsigned int N>
bool enter_regions(std::array<int, N> regions_to_enter) {
    mutex.lock();
    for (auto region : regions_to_enter) {
        if (regions[region]) {
            mutex.unlock();
            return false;
        }
    }
    for (auto region : regions_to_enter) {
        regions[region] = true;
        std::cout << "registring region " << region << '\n';
    }
    mutex.unlock();
    return true;
}

void exit_region( int region ) {
    mutex.lock();
    regions[region] = false;
    std::cout << "exiting region " << region << '\n';
    mutex.unlock();
}

void Train::run(){
    while (true) {
        msleep(201 - speed);

        if ( curr_pos.x < start_pos.x + 250 && curr_pos.y == start_pos.y ) {
            if (curr_pos.x == start_pos.x + 230) {
                if (ID == 1) {
                    if (!enter_regions<2u>({0, 2})) {
                        continue;
                    }
                } else if (ID == 2) {
                    if (!enter_regions<4u>({0, 1, 3, 4})) {
                        continue;
                    }
                }
            } else {
                if (curr_pos.x == start_pos.x) {
                    if (ID == 2) {
                        exit_region(0);
                    } else if (ID == 3) {
                        exit_region(1);
                    }  else if (ID == 5) {
                        exit_region(2);
                    }
                } else if (curr_pos.x == start_pos.x + 135) {
                    if (ID == 4) {
                        exit_region(2);
                    } else if (ID == 5) {
                        exit_region(4);
                    }
                }
            }
            curr_pos.x += 5;
        } else if ( curr_pos.x == start_pos.x + 250 && curr_pos.y < start_pos.y + 120 ) {
            if (curr_pos.y == start_pos.y + 20) {
                if (ID == 4) {
                    exit_region(3);
                } else if (ID == 5) {
                    exit_region(5);
                }
            }
            curr_pos.y += 5;
        } else if ( curr_pos.x > start_pos.x - 20 && curr_pos.y == start_pos.y + 120 ) {
            if (curr_pos.x == start_pos.x + 135) {
                if (ID == 3) {
                    if (!enter_regions<2u>({1, 5})) {
                        continue;
                    }
                }
            } else if (curr_pos.x == start_pos.x) {
                if (ID == 5) {
                    if (!enter_regions<3u>({4, 5, 6})) {
                        continue;
                    }
                }
            } else {
                if (curr_pos.x == start_pos.x + 230) {
                    if (ID == 1) {
                        exit_region(0);
                    } else if (ID == 2) {
                        exit_region(1);
                    } else if (ID == 4) {
                        exit_region(6);
                    }
                } else if (curr_pos.x == start_pos.x + 95) {
                    if (ID == 1) {
                        exit_region(2);
                    } else if (ID == 2) {
                        exit_region(4);
                    }
                }
            }
            curr_pos.x -= 5;
        } else {
            if (curr_pos.y == start_pos.y + 20) {
                if (ID == 4) {
                    if (!enter_regions<3u>({2, 3, 6})) {
                        continue;
                    }
                }
            } else {
                if (curr_pos.y == start_pos.y + 100) {
                    if (ID == 2) {
                        exit_region(3);
                    } else if (ID == 3) {
                        exit_region(5);
                    }
                }
            }
            curr_pos.y -= 5;
        }
        emit updateGUI(ID, curr_pos.x, curr_pos.y);
    }
}

void Train::setSpeed( int speed ) {
    this->speed = speed;
    if (speed == 0)
        this->terminate();
    else if (!this->isRunning())
        this->start();
}
