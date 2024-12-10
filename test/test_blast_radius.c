#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include "../src/blast_radius/blast_radius.h"
#include "src/map/map.h"


void test_blast_radius_func(void);


int main(void) {

    test_blast_radius_func();

    return 0;
}


void test_blast_radius_func(void)
{
    int mapSize = 20;
    int amount_of_mines = 0;
    mapPoint* map = NULL;
    map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);
    create_map(mapSize, map, &amount_of_mines);

    for (int y = 0; y < mapSize; y++)
    {
        for (int x = 0; x < mapSize; x++)
        {
            mapPoint* cell = get_cell(map, mapSize, y, x);
            if (cell->point_value == MINE_ENUM)
            {
                cell->point_value = EXPLOSIVE_ENUM;
            }
        }
    }
    blast_radius(mapSize, map);

    for (int y = 0; y < mapSize; y++)
    {
        for (int x = 0; x < mapSize; x++)
        {
            mapPoint* cell = get_cell(map, mapSize, y, x);
            if (cell->point_value == EXPLOSIVE_ENUM)
            {
                for (int dy = y-1; dy <= y+1; dy++)
                {
                    for (int dx = x-1; dx <= x+1; dx++)
                    {
                        if (dx >= 0 && dx < mapSize && dy >= 0 && dy < mapSize)
                        {
                            assert(get_cell(map, mapSize,dy, dx)->point_value   == BLAST_RADIUS_ENUM ||
                                get_cell(map, mapSize,dy, dx)->point_value      == EXPLOSIVE_ENUM);
                        }
                    }
                }

            }
        }
    }
    free(map);
}
