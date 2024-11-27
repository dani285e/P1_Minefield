#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "deminers.h"

int deminer() { //this is a replacement for the fake int main(void) function that was here previously, runs the rest of the file - call it w/e or write it out

    int mapSize;


    char* map = NULL;

    char* temp_route = NULL;
    char* elevation = NULL;

    srand(time(NULL));

    createMap(&mapSize, &map);
    printMap(map, mapSize);

    int deminers = get_deminers(map, mapSize);
    printf("Deminers needed: %d\n", deminers);

    int y = 4;
    int x = 5;
    switch (is_mine(map, mapSize, y, x)) {
        case (1): printf("there is a mine at: %d,%d\n", x, y);
            break;
        case (0): printf("there is NOT a mine at: %d,%d\n", x, y);
            break;
        default: printf("pardon?");
    }

    create_temproute(mapSize, &temp_route);
    printMap(temp_route, mapSize);

    create_elevation_map(mapSize,&elevation);
    printMap(elevation, mapSize);

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
            int outcome = (rand() % MINES) + 1;
            char* cell = getCell(*temp_route, mapSize, y, x); // Sætter cell pointeren lig med den pointer vi får tilbage af getCell funktionen
            if(outcome == 1) {
                *cell = MINE_SYMBOL;
            } else if (outcome > 1 && outcome < 5) {
                *cell = PATH_SYMBOL;
            } else { //only path symbol for as big as map size
                for (int i = 0; i < mapSize; ++i) {
                    *cell = BLANK_SYMBOL;
                }
            }
        }
    }
}

void create_elevation_map(int mapSize, char** elevation_map) {
    char* cell; // Cell er en pointer til en char
    *elevation_map = (char*)malloc(mapSize*mapSize*sizeof(char));

    for (int y = 0; y < mapSize; y++) { // Nested for loop der kører igennem alle pladser i 2D arrayet
        for (int x = 0; x < mapSize; x++) {
            int outcome = (rand() % mapSize) + 1;
            cell = getCell(*elevation_map, mapSize, y, x); // Sætter cell pointeren lig med den pointer vi får tilbage af getCell funktionen
            if(outcome == 1) {
                *cell = HILL_SYMBOL;
            } else { //only path symbol for as big as map size
                for (int i = 0; i < mapSize; ++i) {
                    *cell = BLANK_SYMBOL;
                }
            }
        }
    }

    char* upper_left;

    for (int y = 0; y < mapSize; y++) {
        // Nested for loop der kører igennem alle pladser i 2D arrayet
        for (int x = 0; x < mapSize; x++) {
            char *cell = getCell(*elevation_map, mapSize, y, x);
            if ( *cell == HILL_SYMBOL) {
                upper_left = getCell(*elevation_map, mapSize, y-1, x-1);
                *upper_left = LESS_ELEVATION_SYMBOL; //top left corner
                elevation_map[y-1][x]   = LESS_ELEVATION_SYMBOL;
                elevation_map[y-1][x+1] = LESS_ELEVATION_SYMBOL;
                elevation_map[y][x-1]   = LESS_ELEVATION_SYMBOL;
                elevation_map[y][x]     = LESS_ELEVATION_SYMBOL;
                elevation_map[y][x+1]   = LESS_ELEVATION_SYMBOL;
                elevation_map[y+1][x-1] = LESS_ELEVATION_SYMBOL;
                elevation_map[y+1][x]   = LESS_ELEVATION_SYMBOL;
                elevation_map[y+1][x+1] = LESS_ELEVATION_SYMBOL;
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

    //deminer count is map size divded by 5 and mine amount divdied by 5, which is a constant
    // so that the amount of deminers is dependent on map size and mine amount.
    // meaning 1 deminers for each 5 unit of area and 1 deminer for 5 mines
    int deminer_count = (mapSize/5) + (mineCounter/5) ;

    return deminer_count;
}

int is_mine(char* map, int mapSize, int y, int x) {
    if (*getCell(map, mapSize, y, x) == 'M') {
        return 1;
    }
    return 0;
}



double cell_time(char* map, int mapSize, char* route, char* elevation_map, int y, int x) {
    //check the route map if the cell is part of the path
    if (*getCell(route, mapSize, y, x) == PATH_SYMBOL) {
        double incline;
        //creates an elevation coefficient from the elevation map
        switch (*getCell(elevation_map, mapSize, y, x)) {
            case HILL_SYMBOL: incline = 1.5;
                break;
            case 'L': incline = 1.2;
                break;
            case 'l': incline = 1.1;
                break;
            default: incline = 1;
        }
        //compares to the mine/obstacle map, what time value to return
        switch (*getCell(map, mapSize, y, x)) {
            case (BLANK_SYMBOL): return incline*BLANK;
            case (OBSTACLE_SYMBOL): return incline*OBSTACLE;
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
        }
    }
    return time_sum;
}


