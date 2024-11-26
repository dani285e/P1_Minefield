//
// Created by Danie on 20-11-2024.
//

#ifndef MAP_H
#define MAP_H
#include "../structs.h"

void createMap(int* mapSize, char** map, Deminer deminer);
void printMap(char* map, int mapSize, Deminer deminer);
void writeToMap(char ** map, int * map_size);

char* getCell(char* map, int mapSize, int y, int x);



#endif //MAP_H
