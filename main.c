
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"

#include "map/map.h"
#include "map/colour/colour.h"
#include "movement/movement.h"


int main(void) {

    int mapSize;
    char* map = NULL;

    srand(time(NULL));

    createMap(&mapSize, &map);
    Deminer mine_remover = {1, 1, 1};
    printMap(map, mapSize, mine_remover);

    movePlayer(&mine_remover, mapSize, map);

    free(map);

    return 0;
}







