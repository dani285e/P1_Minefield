#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MINES 20

enum point_value {
    Clear, Obstacle, Mine};

char point_value_name[3] = {'O', 'X', 'M'};

typedef struct {
    int point_value_x;
    int point_value_y;
    enum point_value point_value;
} mapPoint;

mapPoint* get_cell(mapPoint* map, int mapSize, int y, int x);
void create_map(int mapSize, mapPoint* map);
void print_map(int mapSize, mapPoint* map);
void check_a_point(int mapSize, mapPoint* map);
void red();
void green();
void reset();
void yellow();

int main(void) {

    srand(time(NULL));

    mapPoint* map = NULL;
    int mapSize = (rand()% 20) + 10;
    map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);
    //mapPoint map[1000][1];

    create_map(mapSize, map);
    print_map(mapSize, map);
    check_a_point(mapSize, map);


    free(map);
    map = NULL;

    return 0;
}

mapPoint* get_cell(mapPoint* map, int mapSize, int y, int x) {
    mapPoint* cell = map + mapSize * y + x;
    return cell;
}

void create_map(int mapSize, mapPoint* map) {
    mapPoint* cell;

    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            int outcome = (rand() % MINES) + 1;
            cell = get_cell(map, mapSize, y, x);
            if(outcome == 1) {
                cell->point_value = Mine;

            } else if (outcome > 1 && outcome < 5) {
                cell->point_value = Obstacle;
            } else {
                cell->point_value = Clear;
            }
            cell->point_value_x = x;
            cell->point_value_y = y;
        }
    }

}

void print_map(int mapSize, mapPoint* map) {
    int mineCounter = 0;
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            if (get_cell(map, mapSize, y, x)->point_value == Mine) {
                red();
                printf("%3c", point_value_name[Mine]);
                reset();
                mineCounter++;
            } else if (get_cell(map, mapSize, y, x)->point_value == Obstacle) {
                yellow();
                printf("%3c", point_value_name[Obstacle]);
                reset();
            } else {
                green();
                printf("%3c", point_value_name[Clear]);
                reset();
            }
        }
        printf("\n");
    }
    printf("\n\n\n");
    printf("There is a total of %d mines there needs to be cleared\n\n", mineCounter);
    printf("They are located at the following points\n");
    int counter = 0;
    for(int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            if (get_cell(map, mapSize, y, x)->point_value == Mine) {
                counter = counter + 1;
                printf("Mine %-2d is located at point X = %-2d, Y = %d\n", counter, x, y);
            }
        }
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

void red() {
    printf("\033[0;31m");
}

void green() {
    printf("\033[0;32m");
}

void reset() {
    printf("\033[0m");
}

void yellow() {
    printf("\033[0;33m");
}