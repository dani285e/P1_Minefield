#ifndef START_POINT_H
#define START_POINT_H
#include "start_point.h"
#include <stdio.h>
#include <math.h>
#include "src/map/map.h"
#include "src/structs.h"

///
/// @param y_1
/// @param y_2
/// @param x_1
/// @param x_2
/// @param map
/// @param mapSize
/// @param unit
/// @return
int unit_counter(int y_1, int y_2, int x_1, int x_2, mapPoint* map, int mapSize, int unit);

/// Sammenligningsfunktion, der tager fire ints, og finder den største værdi.
/// @param counter1 Int 1
/// @param counter2 Int 2
/// @param counter3 Int 3
/// @param counter4 Int 4
/// @return Hvis counter1 er størst returneres 1, hvis counter2 returneres 2 osv...
int compare_lines(int counter1, int counter2, int counter3, int counter4);

/// Genererer startpunkter for deminerne, ud fra hvilken linje, der ligger flest miner på.
/// @param mapSize Bruges til at skabe et interval, således at deminerne ikke starter oven på hinanden.
/// @param map Bruges i unit_counter kald.
/// @param deminers Bruges til at sætte deminernes startpositioner.
/// @param amount_of_deminers Bruges som grænse til loops.
void function_find_start_line (int mapSize, mapPoint* map, Deminer* deminers, int amount_of_deminers);
#endif //START_POINT_H
