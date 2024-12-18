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
                *amount_of_mines  += 1;
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

void print_map_info(int mapSize, mapPoint* map, int amount_of_deminers) {
    int mineCounter = unit_counter(0, mapSize-1, 0, mapSize-1, map, mapSize, MINE_ENUM);
    printf("\033[0m");
    printf("\033[0;32m'.' is a Clear Tile\n");
    printf("\033[0;36m'W' is a Walkable Obstacle Tile\n");
    printf("\033[0;33m'X' is a NON-Walkable Obstacle Tile\n");
    printf("\033[0;31m'M' is a Mine\n");
    printf("\033[0;34m'E' is an Explosive\n");
    printf("\033[0;35m'B' is the Blast Radius\n");
    printf("\033[0m'Numbers' are de-miners on the map ranging from 1 to %d\n", amount_of_deminers);
    printf("\033[0m'*' is a Path walked on by a de-miner\n\n");
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
    printf("\n\033[0m");

    int choice = 'b';
    while (choice != 'c') {
        printf("Press c to continue\n");
            scanf(" %c", &choice);
    }
    printf("\n");
}

void user_input_deminers(int mapSize, int* amount_of_deminers) {
    int recommended_amount = ((mapSize * mapSize) / 200) + 1;
    int user_choice = 0;
    printf("\033[0m");
    printf("This is a given map of a minefield\n");
    printf("It has the size %d * %d\n", mapSize, mapSize);
    printf("It is recommended to use %d de-miners\n", recommended_amount);
    while(user_choice < 1 || user_choice > mapSize) {
        printf("\nInput an amount of de-miners\n");
        scanf("%d", &user_choice);
        if (user_choice < 1 || user_choice > mapSize) {
            printf("Invalid amount of de-miners please try again\n");
            while (getchar() != '\n')
            user_choice = 0;
        }
    }
    *amount_of_deminers = user_choice;
}

void run_mode(int* quick_run) {
    int user_choice = 2;
    while (user_choice != 1 && user_choice != 0) {
        printf("\033[0m");
        printf("Select run mode:\nQuick run (press 1)\nRegular run (press 0)\n");
        scanf("%d", &user_choice);
        if (user_choice != 1 && user_choice != 0) {
            printf("Invalid run mode selected please try again\n");
            while (getchar() != '\n');
            user_choice = 2;
        }
    }
    *quick_run = user_choice;
}