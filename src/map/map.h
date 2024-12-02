//
// Created by Danie on 20-11-2024.
//

#ifndef MAP_H
#define MAP_H
#include "src/structs.h"
#include "src/map/colour/colour.h"


mapPoint* getCell(mapPoint* map, int mapSize, int y, int x);

mapPoint* get_cell(mapPoint* map, int mapSize, int y, int x);
void create_map(int mapSize, mapPoint* map, int* amount_of_mines);
void print_map(int mapSize, mapPoint* map, Deminer* deminers, int amount_of_deminers);
void writeToMap(char ** map, int * map_size);
void check_a_point(int mapSize, mapPoint* map);
void red();
void green();
void reset();
void yellow();





#endif //MAP_H
