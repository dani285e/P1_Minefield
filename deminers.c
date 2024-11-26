#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "deminers.h"
#include "terrain.h"
#include "map/map.h"

int deminer() {

    int mapSize = 10;
    Deminer deminer = {};

    char* map = NULL;
    char* temp_route = NULL;
    char* elevation = NULL;

    srand(time(NULL));

    createMap(&mapSize, &map, deminer);
    printf("Mine and obstacle map:\n");
    printMap(map, mapSize, deminer);

    int deminers = get_deminers(map, mapSize);
    printf("\n Deminers needed: %d\n", deminers);

    create_temproute(mapSize, &temp_route);
    printf("Temporary path map\n");
    printMap(temp_route, mapSize, deminer);

    create_elevation_map(mapSize, &elevation);
    update_map(elevation, mapSize);
    printf("Elevation map\n");
    printMap(elevation, mapSize, deminer);

    printf("it takes %lf minutes to walk the route", total_time(map, mapSize, temp_route, elevation));

    free(map);
    free(temp_route);
    free(elevation);

    return 0;
}

void create_temproute(int mapSize, char** temp_route) {
    //char* cell; // Cell er en pointer til en char

    *temp_route = (char*)malloc(mapSize*mapSize*sizeof(char));

    for (int y = 0; y < mapSize; y++) { // Nested for loop der kører igennem alle pladser i 2D arrayet
        for (int x = 0; x < mapSize; x++) {
            int outcome = (rand() % HILLS) + 1;
            char* cell = getCell(*temp_route, mapSize, y, x); // Sætter cell pointeren lig med den pointer vi får tilbage af getCell funktionen
            if(outcome == 1) {
                *cell = PATH_SYMBOL;
            } else if (outcome > 1 && outcome < 5) {
                *cell = BLANK_SYMBOL;
            } else { //only path symbol for as big as map size
                for (int i = 0; i < mapSize; ++i) {
                    *cell = BLANK_SYMBOL;
                }
            }
        }
    }
}

int get_deminers(char* map, int mapSize) {
    int mineCounter = 0;
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            if (*getCell(map, mapSize, y, x) == 'M') {
                mineCounter++;
            }
        }
    }

    int size_deminers;
    int mines_deminers;

    size_deminers = mapSize/10;     //1 deminer for each 10 units
    mines_deminers = mineCounter/5; //1 deminer for each 5 mines

    //returns the biggest value of the deminers proportional to size vs. deminers proportional to mines
    if (size_deminers > mines_deminers) {
        return size_deminers;
    }
    if (size_deminers < mines_deminers) {
        return mines_deminers;
    }

    return 1; //default minimum amount of deminers needed
}



double cell_time(char* map, int mapSize, char* route, char* elevation_map, int y, int x) {
    double incline;
    //check the route map if the cell is part of the path
    if (*getCell(route, mapSize, y, x) == PATH_SYMBOL) {
        //creates an elevation coefficient from the elevation map
        switch (*getCell(elevation_map, mapSize, y, x)) {
            case HILL_SYMBOL: incline = 1.2;
                break;
            case LESS_ELEVATION_SYMBOL: incline = 1.1;
                break;
            default: incline = 1;
        }
        //compares to the mine/obstacle map, what time value to return
        switch (*getCell(map, mapSize, y, x)) {
            case (BLANK_SYMBOL): return incline*BLANK;
            case (OBSTACLE_SYMBOL): return incline*BLANK + OBSTACLE;
            case (MINE_SYMBOL): return (incline*BLANK) + DEMINING_TIME;
            default: return 0;
        }
    }
    return 0;
}

double total_time(char* map, int mapSize, char* route, char* elevation) {
    double time_sum = 0;
    for (int y = 0; y < mapSize; ++y) {
        for (int x = 0; x < mapSize; ++x) {
            time_sum += cell_time(map, mapSize, route, elevation, y, x);
            //printf("cell time: %lf\n", time_sum); //shows updated time for each cell
        }
    }
    return time_sum;
}


