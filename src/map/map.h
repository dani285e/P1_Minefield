//
// Created by Danie on 20-11-2024.
//

#ifndef MAP_H
#define MAP_H
#include "src/structs.h"


void createMap(int* mapSize, mapPoint** map);
void printMap(mapPoint* map, int mapSize, Deminer deminer);
void writeToMap(char ** map, int * map_size);

mapPoint* getCell(mapPoint* map, int mapSize, int y, int x);

mapPoint* get_cell(mapPoint* map, int mapSize, int y, int x);
void create_map(int mapSize, mapPoint* map);
void print_map(int mapSize, mapPoint* map);
void check_a_point(int mapSize, mapPoint* map);
void red();
void green();
void reset();
void yellow();





#endif //MAP_H
