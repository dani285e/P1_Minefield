//
// Created by Danie on 20-11-2024.
//



#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "../structs.h"



void move_up(Deminer *deminer);
void move_down(Deminer *deminer);
void move_left(Deminer *deminer);
void move_right(Deminer *deminer);

void move(Deminer *deminer, int direction);
void movePlayer(Deminer * deminer, int mapSize, char * map);

#endif //MOVEMENT_H
