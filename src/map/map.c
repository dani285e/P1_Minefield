#include <stdio.h>
#include <stdlib.h>
#include "map.h"


#define MINES 20

mapPoint* get_cell(mapPoint* map, int mapSize, int y, int x) {
    mapPoint* cell = map + mapSize * y + x;
    return cell;
}

void create_map(int mapSize, mapPoint* map) {
    mapPoint* cell;

    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            int outcome = (rand() % MINES) + 1;
            cell = get_cell(map, mapSize, y, x);
            if(outcome == 1) {
                cell->point_value = MINE_ENUM;

            } else if (outcome > 1 && outcome < 5) {
                cell->point_value = OBSTACLE_ENUM;
            } else {
                cell->point_value = CLEAR_ENUM;
            }
            cell->point_value_x = x;
            cell->point_value_y = y;
        }
    }
}

void print_map(int mapSize, mapPoint* map) {
    int mineCounter = 0;
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            if (get_cell(map, mapSize, y, x)->point_value == MINE_ENUM) {
                red();
                printf("%3c", point_value_name[MINE_ENUM]);
                reset();
                mineCounter++;
            } else if (get_cell(map, mapSize, y, x)->point_value == OBSTACLE_ENUM) {
                yellow();
                printf("%3c", point_value_name[OBSTACLE_ENUM]);
                reset();
            } else {
                green();
                printf("%3c", point_value_name[CLEAR_ENUM]);
                reset();
            }
        }
        printf("\n");
    }
    printf("\n\n\n");
    printf("There is a total of %d mines there needs to be cleared\n\n", mineCounter);
    printf("They are located at the following points\n");
    int counter = 0;
    for(int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            if (get_cell(map, mapSize, y, x)->point_value == MINE_ENUM) {
                counter = counter + 1;
                printf("Mine %-2d is located at point X = %-2d, Y = %d\n", counter, x, y);
            }
        }
    }
}



void check_a_point(int mapSize, mapPoint* map) {
    int current_x;
    int current_y;
    printf("\nCheck the value at a certain point by entering a X and Y coordinate\n");
    scanf("%d", &current_x);
    scanf("%d", &current_y);
    if(current_x < 0 || current_x >= mapSize || current_y < 0 || current_y >= mapSize) {
        printf("Cant access a point is outside of the map\n");
    } else {
        printf("At point X:%d, Y:%d there is located %c",
        get_cell(map, mapSize, current_y, current_x)->point_value_x,
        get_cell(map, mapSize, current_y, current_x)->point_value_y,
        point_value_name[get_cell(map, mapSize, current_y, current_x)->point_value]);
    }
}