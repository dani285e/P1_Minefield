#include <stdio.h>
#include <stdlib.h>

#include "deminers.h"


void update_map (char* map, int mapSize);
void update_Surrounding_Cells(char* map, int mapSize, int y, int x, char newVal);
void create_elevation_map(int mapSize, char** map);




