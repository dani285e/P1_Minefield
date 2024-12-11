#include <assert.h>

#include "../src/deminers/deminers.h"
#include "../src/path/path.h"
#include "../src/map/map.h"
#include "../src/path/start_point/start_point.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MINES 20

void test_obstacles();
void test_walkable_obstacle();

int main(void) {

    test_obstacles();
    test_walkable_obstacle();

    return 0;
}

void test_obstacles() {
    //deminer();
    srand(time(NULL));

    //int mapSize = (rand()% 20) + OBSTACLE_ENUM0;
    int mapSize = 20;

    mapPoint* map = NULL;
    map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);
    
    int array[20][20] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, MINE_ENUM, OBSTACLE_ENUM, DEMINER_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    int amount_of_deminers = 1;
    Deminer* deminers = NULL;
    deminers = (Deminer*)malloc(sizeof(Deminer)*amount_of_deminers);

    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            map[y * mapSize + x].point_value_x = x;
            map[y * mapSize + x].point_value_y = y;
            map[y * mapSize + x].point_value = array[y][x];
            if (array[y][x] == DEMINER_ENUM) {
                deminers[0].x = x;
                deminers[0].y = y;
                deminers[0].time_taken = 0;
                deminers[0].distance = 0;
                map[y * mapSize + x].point_value = CLEAR_ENUM;
            }
        }
    }

    int continue_continue = 0;

    find_shortest_path(mapSize, map, amount_of_deminers, deminers, continue_continue);

    int time_spent = 44;
    assert(time_spent == deminers[0].time_taken);

    free(map);
    free(deminers);
}

void test_walkable_obstacle() {
      //deminer();
    srand(time(NULL));

    //int mapSize = (rand()% 20) + OBSTACLE_ENUM0;
    int mapSize = 20;

    mapPoint* map = NULL;
    map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);

    int array[20][20] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, OBSTACLE_WALKABLE_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, MINE_ENUM, OBSTACLE_WALKABLE_ENUM, DEMINER_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    int amount_of_deminers = 1;
    Deminer* deminers = NULL;
    deminers = (Deminer*)malloc(sizeof(Deminer)*amount_of_deminers);

    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            map[y * mapSize + x].point_value_x = x;
            map[y * mapSize + x].point_value_y = y;
            map[y * mapSize + x].point_value = array[y][x];
            if (array[y][x] == DEMINER_ENUM) {
                deminers[0].x = x;
                deminers[0].y = y;
                deminers[0].time_taken = 0;
                deminers[0].distance = 0;
                map[y * mapSize + x].point_value = CLEAR_ENUM;
            }
        }
    }

    int continue_continue = 0;

    find_shortest_path(mapSize, map, amount_of_deminers, deminers, continue_continue);

    int time_spent = 7;
    assert(time_spent == deminers[0].time_taken);

    free(map);
    free(deminers);
}