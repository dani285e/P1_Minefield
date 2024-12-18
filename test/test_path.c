#include "../src/path/path.h"
#include <assert.h>
#include <time.h>


void test_path(void);
void test_shortest_path(void);

int main(void) {
    test_path();
    test_shortest_path();

    return 0;
}

void test_path()
{
    int mapSize = 20;
    int amount_of_mines = 0;
    int amount_of_deminers = 3;
    int path = 0;
    int stop_scanf = 0;

    Deminer* deminers = NULL;
    deminers = (Deminer*)malloc(sizeof(Deminer)*amount_of_deminers);

    mapPoint* map = NULL;
    map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);
    create_map(mapSize, map, &amount_of_mines);

    function_find_start_line (mapSize, map, deminers, amount_of_deminers);
    find_shortest_path(mapSize, map, amount_of_deminers, deminers, stop_scanf);

    for (int x = 0; x < mapSize; x++)
    {
        for (int y = 0; y < mapSize; y++)
        {
            mapPoint* cell = get_cell(map, mapSize, y, x);
            if (cell->point_value == PATH_ENUM)
            {
                path++;
            }
        }
    }
    assert(path != 0);
}

void test_shortest_path() {

    //deminer();
    srand(time(NULL));

    //int mapSize = (rand()% 20) + OBSTACLE_ENUM0;
    int mapSize = 20;

    mapPoint* map = NULL;
    map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);

    int array[20][20] = {
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {5, 1, 0, 1, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
        {0, 2, 0, 0, 0, 1, 0, 2, 0, 0, 0, 2, 0, 0, 2, 0, 2, 0, 0, 2}
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
    print_map(mapSize, map, deminers, amount_of_deminers);

    find_shortest_path(mapSize, map, amount_of_deminers, deminers, continue_continue);

    int time_spent = 89;
    assert(time_spent == deminers[0].time_taken);

    free(map);
    free(deminers);

}