#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "deminers.h"
#include "terrain.h"
#include "map/map.h"



int deminer() { //this is a replacement for the fake int main(void) function that was here previously, runs the rest of the file - call it w/e or write it out

    int mapSize;
    Deminer deminer = {};

    char* map = NULL;

    char* temp_route = NULL;
    char* elevation = NULL;

    srand(time(NULL));

    createMap(&mapSize, &map, deminer);
    printMap(map, mapSize, deminer);

    int deminers = get_deminers(map, mapSize);
    printf("Deminers needed: %d\n", deminers);

    create_temproute(mapSize, &temp_route);
    printMap(temp_route, mapSize, deminer);

    create_elevation_map(mapSize, &elevation);
    //update_map(elevation, mapSize);
    //printMap(elevation, mapSize);

    printf("it takes %lf minutes to walk the route", total_time(map, mapSize, temp_route, elevation));


    free(map);
    free(temp_route);
    free(elevation);

    return 0;
}

// Funktion der genererer en arena
/*void createMap(int* mapSize, char** map) {
    char* cell; // Cell er en pointer til en char
    int mapSizetemp = (rand()% 20) + 10;
    *mapSize = mapSizetemp;
    //printf("Please enter a map size\n");
    //scanf("%d", &mapSizetemp);
    printf("Map size is: %d\n", mapSizetemp);
    *map = (char*)malloc(mapSizetemp*mapSizetemp*sizeof(char));

    for (int y = 0; y < mapSizetemp; y++) { // Nested for loop der kører igennem alle pladser i 2D arrayet
        for (int x = 0; x < mapSizetemp; x++) {
            int outcome = (rand() % MINES) + 1;
            cell = getCell(*map, mapSizetemp, y, x); // Sætter cell pointeren lig med den pointer vi får tilbage af getCell funktionen
            if(outcome == 1) {
                *cell = 'M';
            } else if (outcome > 1 && outcome < 5) {
                *cell = 'X';
            } else {
                *cell = 'O';
            }
        }
    }
}*/

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

/*
char* getCell(char* map, int mapSize, int y, int x) { // getCell funktionen der returnerer en pointer til en char
    char* cell = map + mapSize * x + y;
    return cell;
}

void printMap(char* map, int mapSize) { // printMap funktionen udskriver alle elementer i 2D arrayet

    int mineCounter = 0;
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            if (*getCell(map, mapSize, y, x) == 'M') {
                red();
                printf("%2c", *getCell(map, mapSize, y, x));
                reset();
                mineCounter++;
            } else if (*getCell(map, mapSize, y, x) == 'X') {
                yellow();
                printf("%2c", *getCell(map, mapSize, y, x));
                reset();
            } else {
                green();
                printf("%2c", *getCell(map, mapSize, y, x)); // Udskriver den værdi der ligger på hver plads i 2D arrayet
                reset();
            }
        }
        printf("\n");
    }
    printf("\n\n");
    printf("There is a total of %d mines there needs to be cleared\n", mineCounter);
    printf("They are located at the following points\n");
    int counter = 0;
    for(int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            if (*getCell(map, mapSize, y, x) == 'M') {
                counter = counter + 1;
                printf("%-2d Mine: X = %-2d, Y = %d\n", counter, x, y);
            }
        }
    }
}

void red() {
    printf("\033[0;31m");
}

void green() {
    printf("\033[0;32m");
}

void reset() {
    printf("\033[0m");
}

void yellow() {
    printf("\033[0;33m");
}
*/
int get_deminers(char* map, int mapSize) {
    int mineCounter = 0;
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            if (*getCell(map, mapSize, y, x) == 'M') {
                mineCounter++;
            }
        }
    }

    int deminer_count;
    int size_deminers;
    int mines_deminers;

    //if mapsize and minecounter is small, only one deminer is needed
    if (mapSize < 20 || mineCounter < 5) {
        deminer_count = 1;
    }
    //switch for deminers needed proportional to size
    switch (mapSize) {
        case 20: size_deminers = 2;
        case 30: size_deminers = 3;
        default: size_deminers = 1;
    }
    //switch for deminers needed proportional to mine counter values
    switch (mineCounter) {
        case 5: mines_deminers = 2;
            break;
        case 10: mines_deminers = 3;
            break;
    }

    //returns which variable is biggest
    if (mines_deminers < size_deminers) {
        return size_deminers;
    }
    if (mines_deminers > size_deminers) {
        return mines_deminers;
    }

    return deminer_count;
}



double cell_time(char* map, int mapSize, char* route, char* elevation_map, int y, int x) {
    double incline;
    //check the route map if the cell is part of the path
    if (*getCell(route, mapSize, y, x) == PATH_SYMBOL) {
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


