#ifndef START_POINT_H
#define START_POINT_H
#include "start_point.h"
#include <stdio.h>
#include <math.h>
#include "src/map/map.h"

int unit_counter(int y_1, int y_2, int x_1, int x_2, mapPoint* map, int mapSize, int unit);
int compare_lines(int counter1, int counter2, int counter3, int counter4);
void function_find_start_line (int mapSize, mapPoint* map, Deminer* deminers, int amount_of_deminers);
#endif //START_POINT_H
