#include "src//deminers/deminers.h"
#include "src/path/path.h"
#include "src/map/map.h"
#include "src/path/start_point/start_point.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#define MINES 20

int main(void) {

    //deminer();
    srand(time(NULL));

    mapPoint* map = NULL;
    //int mapSize = (rand()% 20) + 10;
    int mapSize = 20;
    int amount_of_mines = 0;
    int amount_of_deminers = 3; //TODO SKAL VÆRE GIVET FRA EN ANDEN FUNKTION
    map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);
    Deminer* deminers = NULL;
    deminers = (Deminer*)malloc(sizeof(Deminer)*amount_of_deminers);

    create_map(mapSize, map, &amount_of_mines);
    initial_print_map(mapSize, map);
    continue_check();
    function_find_start_line(mapSize, map, deminers, amount_of_deminers);
    continue_check();
    print_map_info(mapSize, map);
    find_shortest_path(mapSize, map, amount_of_deminers, deminers);

    free(map);
    free(deminers);

    return 0;
}










