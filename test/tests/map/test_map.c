//
// Created by danie on 09-12-2024.
//

#include "test_map.h"




void test_get_cell()
{
    int mapSize = 20;
    int amount_of_mines = 0;

    mapPoint* map = NULL;
    map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);
    create_map(mapSize, map, &amount_of_mines);

    int x = 5;
    int y = 5;
    mapPoint* cell = get_cell(map, mapSize, y, x);

    assert(cell->point_value_x == x);
    assert(cell->point_value_y == y);

    free(cell);
    free(map);
}

void test_create_map()
{
    int mapSize = 20;
    int amount_of_mines = 0;
    int obstacles = 0;
    int walkable_obstacles= 0;
    int clear = 0;
    int mines = 0;


    
    mapPoint* map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);
    create_map(mapSize, map, &amount_of_mines);


    for (int x = 0; x < mapSize; x++)
    {
        for (int y = 0; y < mapSize; y++)
        {
            mapPoint* cell = get_cell(map, mapSize, y, x);
            switch (cell->point_value)
            {
            case MINE_ENUM:
                mines++;
                break;

            case OBSTACLE_ENUM:
                obstacles++;
                break;

            case OBSTACLE_WALKABLE_ENUM:
                walkable_obstacles++;
                break;

            case CLEAR_ENUM:
                clear++;
                break;
            default: break;;
            }
        }
    }

    assert(mines != 0 && obstacles != 0 && walkable_obstacles != 0 && clear != 0);
}