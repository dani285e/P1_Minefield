#include <assert.h>
#include "../src/path/path.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
void test_time();

int main() {

    test_time();

    return 0;
}

void test_time() {
    //deminer();
    srand(time(NULL));

    //int mapSize = (rand()% 20) + OBSTACLE_ENUM0;
    int mapSize = 20;

    mapPoint* map = NULL;
    map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);

    int array[20][20] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {DEMINER_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, MINE_ENUM, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {DEMINER_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, MINE_ENUM, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {DEMINER_ENUM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, MINE_ENUM, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    int amount_of_deminers = 3;
    Deminer* deminers = NULL;
    deminers = (Deminer*)malloc(sizeof(Deminer)*amount_of_deminers);
    int deminer_count = 0;

    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            map[y * mapSize + x].point_value_x = x;
            map[y * mapSize + x].point_value_y = y;
            map[y * mapSize + x].point_value = array[y][x];
            if (array[y][x] == DEMINER_ENUM) {
                deminers[deminer_count].x = x;
                deminers[deminer_count].y = y;
                deminers[deminer_count].time_taken = 0;
                deminers[deminer_count].distance = 0;
                map[y * mapSize + x].point_value = CLEAR_ENUM;
                deminer_count++;
            }
        }
    }

    int quick_run = 1;

    find_shortest_path(mapSize, map, amount_of_deminers, deminers, quick_run);

    int time_spent_overall = 60;
    int time_spent_each = 20;


    assert(time_spent_each == deminers[0].time_taken &&
            time_spent_each == deminers[1].time_taken &&
            time_spent_each == deminers[2].time_taken);

    int time_spent_deminers = deminers[0].time_taken + deminers[1].time_taken + deminers[2].time_taken;
    assert(time_spent_overall == time_spent_deminers);

    free(map);
    free(deminers);
}