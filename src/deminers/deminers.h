#ifndef DEMINERS_H
#define DEMINERS_H
#include "src/map/map.h"

#define MINES 20
#define HILLS 3


#define DEMINING_TIME 10 //assumption it takes 10 minutes to demine 1 mine
#define BLANK 1 //assumption it takes 1 minutes to walk across empty field
#define OBSTACLE 3 //assumption it takes 3 minutes to walk around field with obstacle



int get_deminers(mapPoint* map, int mapSize); //takes map size and amount of mines to calculate deminers needed
int is_mine(mapPoint* map, int mapSize, int y, int x); //checks boolean if cell is mine

void create_temproute(int mapSize, mapPoint** temp_route); //temp map to compare with
void create_elevation_map(int mapSize, mapPoint** elevation_map); //map with 'B' elevations

double cell_time(mapPoint* map, int mapSize, mapPoint* route, mapPoint* elevation_map, int y, int x); //checks time for each cell that is on the path
double total_time(mapPoint* map, int mapSize, mapPoint* route, mapPoint* elevation); //checks time of route

int deminer();

#endif