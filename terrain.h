#include <stdio.h>
#include <stdlib.h>

#include "deminers.h"

//creates elevation map. with symbols 'B' for bakke and 'O' for blank.
void create_elevation_map(int mapSize, char** map);
//updates map with 'L' around 'B' for the less elevation.
void update_map (char* map, int mapSize);
//helper function to update map
void update_Surrounding_Cells(char* map, int mapSize, int y, int x, char newVal);





