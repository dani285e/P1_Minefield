//
// Created by Danie on 20-11-2024.
//

#include "movement.h"

#include <stdio.h>

void move_up(Deminer *deminer) {
    deminer->y++;
}
void move_down(Deminer *deminer) {
    deminer->y--;
}
void move_left(Deminer *deminer) {
    deminer->x--;
}
void move_right(Deminer *deminer) {
    deminer->x++;
}

/**
 *
 * @param deminer The deminer that needs to be moved
 * @param direction 1: Up, 2: Down, 3: Left, 4: Right
 */
void move(Deminer *deminer, int direction) {
    switch (direction) {
        case 1:
            move_up(deminer);
        break;
        case 2:
            move_down(deminer);
        break;
        case 3:
            move_left(deminer);
        break;
        case 4:
            move_right(deminer);
        break;

        default:
            printf("Failed to move mine_remover");
    }
}

void movePlayer(Deminer * mine_remover, int mapSize, char *map) {
    move(mine_remover, 2);
    printMap(map, mapSize, *mine_remover);
    move(mine_remover, 3);
    printMap(map, mapSize, *mine_remover);
    move(mine_remover, 4);
    printMap(map, mapSize, *mine_remover);
    move(mine_remover, 1);
    printMap(map, mapSize, *mine_remover);
}
