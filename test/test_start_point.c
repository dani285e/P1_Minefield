#include "../src/path/start_point/start_point.h"
#include "../src/structs.h"
#include <assert.h>
void test_unit_counter();
void test_compare_lines();
void test_find_start_line();

int main(void) {
    test_find_start_line();
    test_unit_counter();
    test_compare_lines();
    return 0;
}

// START POINT / LINE
void test_unit_counter()
{
    int mapSize = 20;
    int amount_of_mines = 0;

    mapPoint* map = NULL;
    map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);
    create_map(mapSize, map, &amount_of_mines);

    int mines = unit_counter(0, mapSize-1, 0, mapSize-1, map, mapSize, MINE_ENUM);
    assert(amount_of_mines == mines);
}

void test_compare_lines()
{
    assert(compare_lines(1, 2, 3, 4) == 4);
    assert(compare_lines(1, 2, 4, 3) == 3);
    assert(compare_lines(1, 4, 3, 2) == 2);
    assert(compare_lines(4, 3, 2, 1) == 1);
}

void test_find_start_line()
{
    int mapSize = 20;
    int amount_of_mines = 0;

    mapPoint* map = NULL;
    map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);
    create_map(mapSize, map, &amount_of_mines);

    Deminer deminers[3];
    int amount_of_deminers = 3;
    for (int i = 0; i < amount_of_deminers; i++)
    {
        deminers[i].x = -1;
        deminers[i].y = -1;
    }

    double size = mapSize;
    int top_counter = unit_counter(0, ceil(size/2)-1, 0, mapSize-1, map, mapSize, MINE_ENUM);
    int left_counter = unit_counter(0, mapSize-1, 0, ceil(size/2)-1, map, mapSize, MINE_ENUM);
    int right_counter = unit_counter(0, mapSize-1, floor(size/2), mapSize-1, map, mapSize, MINE_ENUM);
    int bottom_counter = unit_counter(floor(size/2), mapSize-1, 0, mapSize-1, map, mapSize, MINE_ENUM);
    printf("top counter: %d\n", top_counter);
    printf("left counter: %d\n", left_counter);
    printf("right counter: %d\n", right_counter);
    printf("bottom_counter: %d\n", bottom_counter);

    function_find_start_line(mapSize, map, deminers, amount_of_deminers);
    int start_line = compare_lines(top_counter, left_counter, right_counter, bottom_counter);
    int deminers_placed = 0;

    for (int i = 0; i < amount_of_deminers; i++)
    {
        switch (start_line)
        {
            case 1:
                if (deminers[i].x >= 0 &&
                    deminers[i].x < mapSize &&
                    deminers[i].y == 0)
                {
                    deminers_placed++;
                }
                break;
            case 2:
                if (deminers[i].x == 0 &&
                    deminers[i].y >= 0 &&
                    deminers[i].y < mapSize)
                {
                    deminers_placed++;
                }
                break;
            case 3:
                if (deminers[i].x == mapSize-1 &&
                    deminers[i].y >= 0 &&
                    deminers[i].y < mapSize)
                {
                    deminers_placed++;
                }
                break;
            case 4:
                if (deminers[i].x >= 0 &&
                    deminers[i].x < mapSize &&
                    deminers[i].y == mapSize-1)
                {
                    deminers_placed++;
                }
                break;
            default: printf("How did you get here. Im a test and you dont have a startline between 1-4\n");
        }
    }
    assert(deminers_placed == amount_of_deminers);
}
