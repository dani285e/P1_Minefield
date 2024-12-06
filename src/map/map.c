#include "map.h"
#define MINES 20

mapPoint* get_cell(mapPoint* map, int mapSize, int y, int x) {
    mapPoint* cell = map + mapSize * y + x;
    return cell;
}

void create_map(int mapSize, mapPoint* map, int* amount_of_mines) {
    mapPoint* cell;

    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            int outcome = (rand() % MINES) + 1;
            cell = get_cell(map, mapSize, y, x);
            if(outcome == 1) {
                cell->point_value = MINE_ENUM;
                *amount_of_mines++;
            } else if (outcome > 1 && outcome < 5) {
                cell->point_value = OBSTACLE_ENUM;
            } else if (outcome > 6 && outcome < 9) {
                cell->point_value = OBSTACLE_WALKABLE_ENUM;
            } else {
                cell->point_value = CLEAR_ENUM;
            }
            cell->point_value_x = x;
            cell->point_value_y = y;
        }
    }
}

void initial_print_map(int mapSize, mapPoint* map) {
    mapPoint* cell;
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            cell = get_cell(map, mapSize, y, x);
            printf("%s%3c",point_value_color[cell->point_value], point_value_name[cell->point_value]);
        }
        printf("\n%s", point_value_color[4]);
    }
    printf("\033[0m");
    printf("\n\nThis is a given map of a minefield\n");
}


void print_map(int mapSize, mapPoint* map, Deminer* deminers, int amount_of_deminers) {
    mapPoint* cell;
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            cell = get_cell(map, mapSize, y, x);
            int hit_a_value = 0;
            for (int i = 0; i < amount_of_deminers; i++) {
                if (cell->point_value_x == deminers[i].x && cell->point_value_y == deminers[i].y) {
                    printf("%s%3d",point_value_color[DEMINER_ENUM], i+1);
                    hit_a_value = 1;
                }
            }
            if (hit_a_value == 0) {
                printf("%s%3c",point_value_color[cell->point_value], point_value_name[cell->point_value]);
            }
        }
        printf("\n%s", point_value_color[4]);
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


void print_map_info(int mapSize, mapPoint* map) {
    int mineCounter = unit_counter(0, mapSize-1, 0, mapSize-1, map, mapSize, MINE_ENUM);
    printf("\033[0m");
    printf("\nThere is a total of %d mines there needs to be cleared\n", mineCounter);
    printf("They are located at the following points\n\n");
    int counter = 0;
    for(int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            if (get_cell(map, mapSize, y, x)->point_value == MINE_ENUM) {
                counter = counter + 1;
                printf("Mine %-2d is located at point X = %-2d, Y = %d\n", counter, x, y);
            }
        }
    }
    printf("\n");
}

void continue_check() {
    printf("\033[0m");
    int choice = 'b';
    while (choice != 'c') {
            printf("Press c to continue\n");
            scanf(" %c", &choice);
    }
    printf("\n");
}
