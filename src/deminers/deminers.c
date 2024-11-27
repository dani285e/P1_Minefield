#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deminers.h"



int deminer() { //this is a replacement for the fake int main(void) function that was here previously, runs the rest of the file - call it w/e or write it out


    Deminer deminer;// TODO need a new name

    srand(time(NULL));
    int mapSize = (rand()% 20) + 10;

    mapPoint* map = NULL;
    map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);

    mapPoint* temp_route = NULL;
    temp_route = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);

    mapPoint* elevation = NULL;
    elevation = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);




    create_map(mapSize, map);
    print_map(mapSize, map);

    int deminers = get_deminers(map, mapSize);
    printf("Deminers needed: %d\n", deminers);

    int y = 4;
    int x = 5;
    // switch (is_mine(map, mapSize, y, x)) {
    //     case (1): printf("there is a mine at: %d,%d\n", x, y);
    //         break;
    //     case (0): printf("there is NOT a mine at: %d,%d\n", x, y);
    //         break;
    //     default: printf("pardon?");
    // }

    create_temproute(mapSize, &temp_route);
    print_map(mapSize, temp_route);

    create_elevation_map(mapSize, &elevation);
    print_map(mapSize, elevation);

    printf("it takes %lf minutes to walk the route", total_time(map, mapSize, temp_route, elevation));



    free(map);
    free(temp_route);
    free(elevation);

    map = NULL;

    return 0;
}


void create_temproute(int mapSize, mapPoint** temp_route) {
    //char* cell; // Cell er en pointer til en char

    for (int y = 0; y < mapSize; y++) { // Nested for loop der kører igennem alle pladser i 2D arrayet
        for (int x = 0; x < mapSize; x++) {
            int outcome = (rand() % MINES) + 1;
            mapPoint* cell = get_cell(*temp_route, mapSize, y, x); // Sætter cell pointeren lig med den pointer vi får tilbage af getCell funktionen
            if(outcome == 1) {
                cell->point_value = MINE_ENUM;
            } else if (outcome > 1 && outcome < 5) {
                cell->point_value = PATH_ENUM;
            } else { //only path symbol for as big as map size
                for (int i = 0; i < mapSize; ++i) {
                    cell->point_value = BLANK;
                }
            }
        }
    }
}

void add_hill(int mapSize, mapPoint** elevation_map) {
    mapPoint* cell; // Cell is a pointer to a mapPoint struct

    // Set random cells to Hill
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            int outcome = (rand() % mapSize) + 1;
            cell = get_cell(*elevation_map, mapSize, y, x); // Get pointer to the current cell

            if (outcome == 1) {
                cell->point_value = HILL_ENUM; // Set point value to Hill for hill cells
            } else {
                cell->point_value = CLEAR_ENUM; // Set point value to Clear for non-hill cells
            }
        }
    }
}

void create_elevation_map(int mapSize, mapPoint** elevation_map) {
    mapPoint* cell; // Cell er en pointer til en char
    add_hill(mapSize, elevation_map);


    for (int y = 0; y < mapSize; y++) {
        // Nested for loop der kører igennem alle pladser i 2D arrayet
        for (int x = 0; x < mapSize; x++) {
            cell = get_cell(*elevation_map, mapSize, y, x);
            if (cell->point_value == HILL_ENUM) {
                for (int dy = -1; dy <= 1; dy++){
                    for (int dx = -1; dx <= 1; dx++){

                        if (dy == 0 && dx == 0){
                            continue;
                        }

                        int ny = y + dy;
                        int nx = x + dx;
                        if (ny >= 0 && ny < mapSize && nx >= 0 && nx < mapSize)
                        {
                            get_cell(*elevation_map, mapSize, ny, nx)->point_value = LOWER_ELEVATION_ENUM;
                        }
                    }
                } //TODO missing LESSER_ELEVATION_ENUM after LOWER_ELEVATION_ENUM
            }
        }
    }
}


int get_deminers(mapPoint* map, int mapSize) {
    int mineCounter = 0;
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            if (get_cell(map, mapSize, y, x)->point_value == MINE_ENUM) {
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





double cell_time(mapPoint* map, int mapSize, mapPoint* route, mapPoint* elevation_map, int y, int x) {
    //check the route map if the cell is part of the path
    if (get_cell(route, mapSize, y, x)->point_value == PATH_ENUM ) {
        double incline;
        //creates an elevation coefficient from the elevation map
        switch (get_cell(elevation_map, mapSize, y, x)->point_value) {
            case HILL_ENUM: incline = 1.5;
                break;
            case LOWER_ELEVATION_ENUM: incline = 1.2;
                break;
            case LESSER_ELEVATION_ENUM: incline = 1.1; //TODO MISSING IMPLEMENTATION OF LESSER_ELEVATION_ENUM
                break;
            default: incline = 1;
        }
        //compares to the mine/obstacle map, what time value to return
        switch (get_cell(map, mapSize, y, x)->point_value) {
            case (CLEAR_ENUM): return incline*BLANK;
            case (OBSTACLE_ENUM): return incline*OBSTACLE;
            case (MINE_ENUM): return (incline*BLANK) + DEMINING_TIME;
            default: return 0;
        }
    }
    return 0;
}

double total_time(mapPoint* map, int mapSize, mapPoint* route, mapPoint* elevation) {
    double time_sum = 0;
    for (int y = 0; y < mapSize; ++y) {
        for (int x = 0; x < mapSize; ++x) {
            time_sum += cell_time(map, mapSize, route, elevation, y, x);
        }
    }
    return time_sum;
}


