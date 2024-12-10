#include "../src/path/path.h"
#include <assert.h>


void test_path(void);

int main(void) {
    test_path();

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