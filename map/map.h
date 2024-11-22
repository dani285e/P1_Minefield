//
// Created by Danie on 20-11-2024.
//

#ifndef MAP_H
#define MAP_H
#include "../structs.h"


void createMap(int* mapSize, struct Map* map[]);
char* getCell(char* map, int mapSize, int y, int x);
void printMap(char* map, int mapSize, struct deminer);



#endif //MAP_H
