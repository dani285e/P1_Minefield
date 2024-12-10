#include "deminers/deminers.h"
#include "path/path.h"
#include "map/map.h"
#include "path/start_point/start_point.h"
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
    int continue_continue = 1;
    map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);
    Deminer* deminers = NULL;
    deminers = (Deminer*)malloc(sizeof(Deminer)*amount_of_deminers);

    create_map(mapSize, map, &amount_of_mines);
    initial_print_map(mapSize, map);
    continue_check(continue_continue);
    print_map_info(mapSize, map);
    continue_check(continue_continue);
    function_find_start_line(mapSize, map, deminers, amount_of_deminers);
    print_map(mapSize, map, deminers, amount_of_deminers);
    continue_check(continue_continue);
    find_shortest_path(mapSize, map, amount_of_deminers, deminers, continue_continue);

    free(map);
    free(deminers);

    return 0;
}