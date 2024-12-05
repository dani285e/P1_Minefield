

#include "src//deminers/deminers.h"
#include "src/map/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#define MINES 20


///KØFUNKTIONER TIL BFS
Queue* create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}
void enqueue(Queue* queue, int x, int y, int distance) {
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    new_node->x = x;
    new_node->y = y;
    new_node->distance = distance;
    new_node->next = NULL;

    if (queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}
int dequeue(Queue* queue, int* x, int* y, int* distance) {
    if (queue->front == NULL) {
        return 0; // Køen er tom
    }

    QueueNode* temp = queue->front;
    *x = temp->x;
    *y = temp->y;
    *distance = temp->distance;

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return 1; // Succesfuld fjernelse
}
int is_empty(Queue* queue) {
    return (queue->front == NULL);
}
void free_queue(Queue* queue) {
    QueueNode* current = queue->front;
    while (current != NULL) {
        QueueNode* next = current->next;
        free(current);
        current = next;
    }
    free(queue);
}

mapPoint* get_cell(mapPoint* map, int mapSize, int y, int x);
void check_a_point(int mapSize, mapPoint* map);
int unit_counter(int y_1, int y_2, int x_1, int x_2, mapPoint* map, int mapSize, int unit);
int compare_lines(int counter1, int counter2, int counter3, int counter4);
int find_shortest_path_distance_sorter(const void *ep1, const void *ep2);
void function_find_start_line (int mapSize, mapPoint* map, Deminer* deminers, int amount_of_deminers);
void move_deminer(mapPoint* map, int mapSize, int x, int y);
void print_map_info(int mapSize, mapPoint* map);
int find_closest_deminer(Deminer* deminers, int mapsize, mapPoint* map, int amount_of_deminers, int target_x, int target_y);
void find_shortest_path (int mapSize, mapPoint* map, int amount_of_deminers, Deminer* deminers);

int main(void) {

    //deminer();
    srand(time(NULL));

    mapPoint* map = NULL;
    //int mapSize = (rand()% 20) + 10;
    int mapSize = 20;
    int amount_of_mines = 0;
    int amount_of_deminers = 3; // SKAL VÆRE GIVET FRA EN ANDEN FUNKTION
    map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);
    Deminer* deminers = NULL;
    deminers = (Deminer*)malloc(sizeof(Deminer)*amount_of_deminers);

    create_map(mapSize, map, &amount_of_mines);
    print_map(mapSize, map, deminers, amount_of_deminers);
    function_find_start_line(mapSize, map, deminers, amount_of_deminers);
    print_map(mapSize, map, deminers, amount_of_deminers);
    print_map_info(mapSize, map);
    //check_a_point(mapSize, map);
    //find_shortest_path(mapSize, map, amount_of_mines);
    //print_map(mapSize, map);
    find_shortest_path(mapSize, map, amount_of_deminers, deminers);

    printf("\033[0m");
    int total_distance = 0;
    for (int i = 0; i < amount_of_deminers; i++) {
        printf("Total distance walked for deminer %d is %d\n", i+1,  deminers[i].distance);
        total_distance += deminers[i].distance;
    }
    printf("Total distance walked all deminers is %d\n", total_distance);


    free(map);
    free(deminers);

    return 0;
}


void move_deminer(mapPoint* map, int mapSize, int x, int y) {
    mapPoint* cell;
    cell = get_cell(map, mapSize, y, x);
    cell->point_value = DEMINER_ENUM;
}



void print_map_info(int mapSize, mapPoint* map) {
    int mineCounter = unit_counter(0, mapSize-1, 0, mapSize-1, map, mapSize, MINE_ENUM);
    printf("\n\n\n");
    printf("There is a total of %d mines there needs to be cleared\n\n", mineCounter);
    printf("They are located at the following points\n");
    int counter = 0;
    for(int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            if (get_cell(map, mapSize, y, x)->point_value == MINE_ENUM) {
                counter = counter + 1;
                printf("Mine %-2d is located at point X = %-2d, Y = %d\n", counter, x, y);
            }
        }
    }
}

// Funktion search_map der tager 5 ints og en pointer til map paremeter
int unit_counter(int y_1, int y_2, int x_1, int x_2, mapPoint* map, int mapSize, int unit)
{
    mapPoint* cell;
    int counter = 0;
    // For loop der tæller antal mines for side 1
    for (int y = y_1; y <= y_2; y++) {
        for (int x = x_1; x <= x_2; x++) {
            cell = get_cell(map, mapSize, y, x);
            if(cell->point_value == unit) {
                counter++;
            }
        }
    }
    return counter;
}

void function_find_start_line (int mapSize, mapPoint* map, Deminer* deminers, int amount_of_deminers) {
    double size = mapSize;
    int top_counter = unit_counter(0, ceil(size/2)-1, 0, mapSize-1, map, mapSize, MINE_ENUM);
    int left_counter = unit_counter(0, mapSize-1, 0, ceil(size/2)-1, map, mapSize, MINE_ENUM);
    int right_counter = unit_counter(0, mapSize-1, floor(size/2), mapSize-1, map, mapSize, MINE_ENUM);
    int bottom_counter = unit_counter(floor(size/2), mapSize-1, 0, mapSize-1, map, mapSize, MINE_ENUM);

    printf("Top map is %d\n", top_counter);
    printf("Left map is %d\n", left_counter);
    printf("Right map is %d\n", right_counter);
    printf("Bottom map is %d\n", bottom_counter);

    int start_line = compare_lines(top_counter, left_counter, right_counter, bottom_counter); // Får værdien 1, 2, 3 eller 4 tilbage fra compare_lines
    printf("\nThe start line is: Line %d\n\n", start_line);

    startpoint pointList[amount_of_deminers]; // Listen er ligeså lang som mængden af deminers der er

    int pointcounter = 0;
    double interval = mapSize / (amount_of_deminers); // En int værdi der bruges til at sætte de forskellige startpoints

    // Kan også skrives som switch mere effektivt (run time og calculations)
    if (start_line == 1) { // Hvis start_line == 1 er true vælges genereres startpunkterne på linje top
        for (int i = 0; i < amount_of_deminers; i++) { // For loop der laver amount_of_deminers antal start points
            pointList[pointcounter].start_point_x = ceil((interval / 2) + interval * (i)); // Det næste startpoints x-koordinat vil ikke være det samme som den tidligere
            pointList[pointcounter].start_point_y = 0; // Alle start point vil have y-koordinat = 1, da det er linje 1 vi arbejder på
            pointcounter++; // pointcounter tælles op så et nyt point vil blive lavet
        }
    } else if (start_line == 2) { // Hvis start_line == 2 er true genereres startpunkterne på linje venstre
        for (int i = 0; i < amount_of_deminers; i++) {
            pointList[pointcounter].start_point_x = 0;
            pointList[pointcounter].start_point_y = ceil((interval / 2) + interval * (i));
            pointcounter++;
        }
    } else if (start_line == 3) { // Hvis start_line == 3 er true genereres startpunkterne på linje højre
        for (int i = 0; i < amount_of_deminers; i++) {
            pointList[pointcounter].start_point_x = mapSize-1;
            pointList[pointcounter].start_point_y = ceil((interval / 2) + interval * (i));
            pointcounter++;
        }
    } else { // Ellers genereres startpunkterne på linje bund
        for (int i = 0; i < amount_of_deminers; i++) {
            pointList[pointcounter].start_point_x = ceil((interval / 2) + interval * (i));
            pointList[pointcounter].start_point_y = mapSize-1;
            pointcounter++;
        }
    }

    //mapPoint* cell;
    for(int i = 0; i < amount_of_deminers; i++) { // For loop der kører antal size gange
        deminers[i].x = pointList[i].start_point_x;
        deminers[i].y = pointList[i].start_point_y;
        deminers[i].distance = 0;

        printf("Start point for deminer %d is X:%d, Y:%d\n", i+1, pointList[i].start_point_x, pointList[i].start_point_y);
    }
}

// compare_lines tager 4 ints som parametre den sammenligner dem og returnerer en værdi til function_find_a_start_line
int compare_lines(int counter1, int counter2, int counter3, int counter4) {
    if(counter1 >= counter2 && counter1 >= counter3 && counter1 >= counter4) {
        return 1; // Hvis counter1 er størst returneres 1
    } else if (counter2 >= counter3 && counter2 >= counter4) {
        return 2; // Hvis counter2 er størst returneres 2
    } else if (counter3 >= counter4) {
        return 3; // Hvis counter3 er størst returneres 3
    } else {
        return 4; // Ellers må counter4 være størst og der returneres 4
    }
}


int bfs_find_distance(int mapsize, mapPoint* map, int start_x, int start_y, int target_x, int target_y, int** path, int* path_length) {
    int** visited = malloc(mapsize * sizeof(int*)); //Array, der holder styr på hvilke celler er besøgt.
    mapPoint** prev = malloc(mapsize * sizeof(mapPoint*)); //Array, der holder styr på den endelige rute.
    if (visited == NULL || prev == NULL) {
        printf("Allocation of visited/prev failed, exiting...\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < mapsize; i++) {
        visited[i] = malloc(mapsize* sizeof(int));
        prev[i] = malloc(mapsize * sizeof(mapPoint));
        if (visited[i] == NULL || prev[i] == NULL) {
            printf("Allocation of visited/prev failed, exiting...\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < mapsize; j++) {
            visited[i][j] = 0;
            prev[i][j] = (mapPoint){-1, -1};
        }
    }

    // Retningsvektorer til at navigere op, ned, venstre, højre
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // Kø for BFS: hver entry er {x, y, distance}
    Queue* queue = create_queue();
    enqueue(queue, start_x, start_y, 0);
    visited[start_y][start_x] = 1;

    while (!is_empty(queue)) {
        int x, y, dist;
        dequeue(queue, &x, &y, &dist);

        // Hvis vi har nået målet
        if (x == target_x && y == target_y) {
            *path_length = dist;

            //Tilbagetracker for at finde ruten:
            int current_x = target_x, current_y = target_y; // Start fra målets koordinater

            for (int step = dist; step >= 0; step--) {
                // Find forgængeren fra `prev`
                mapPoint previous_cell = prev[current_y][current_x];


                if (current_x != -1) {
                    path[step][0] = current_x;
                    path[step][1] = current_y;

                    //printf("Path for Deminer %d:\n", );

                    current_x = previous_cell.point_value_x;   // Kolonnen (x-koordinat)
                    current_y = previous_cell.point_value_y;   // Rækken (y-koordinat)
                }
            }

            for (int i = 0; i < mapsize; i++) {
                free(prev[i]);
            }
            free(prev);
            free_queue(queue);
            return dist;
        }

        // Gennemgå alle naboer
        for (int i = 0; i < 4; i++) {
            int new_x = x + directions[i][0];
            int new_y = y + directions[i][1];

            // Tjek om naboen er indenfor gridet og ikke besøgt
            if (new_x >= 0 && new_x < mapsize && new_y >= 0 && new_y < mapsize &&
                !visited[new_y][new_x]) {
                mapPoint* neighbor = get_cell(map, mapsize, new_y, new_x);

                // Tjek om naboen er tilladt
                if (neighbor->point_value != OBSTACLE_ENUM) {
                    visited[new_y][new_x] = 1;
                    prev[new_y][new_x] = (mapPoint){x, y}; //Gemmer forgængeren, så ruten kan konstrueres.

                    enqueue(queue, new_x, new_y, dist + 1);
                }
                }
        }
    }

    for (int i = 0; i < mapsize; i++) {
        free(prev[i]);
    }
    free(prev);
    free_queue(queue);
    return -1; // Returner -1, hvis målet ikke kan nås
}


void reset_path(int** path, int mapsize) {
    //Resetter path-arrayet:
    for (int i = 0; i < mapsize * mapsize; i++) {
        for (int j = 0; j < 2; j++) {
            path[i][j] = -1;
        }
    }
}

// Funktion der skal kunne genererer en rute med hjælp fra Nearest Neighbor Algoritmen
// Først skal den vidde sit startspunkt
// Så skal den kunne vidde afstanden til alle andre miner
// Så skal den vælge den mine der er tættest på og gå hen til den og punktets værdi sættes til 'E'
// Så skal den gøre det hele igen indtil der ikke er flere miner
void find_shortest_path (int mapSize, mapPoint* map, int amount_of_deminers, Deminer* deminers) {
    int amount_of_mines = -1;
    int distance;
    int shortest_distance = 100;
    int shortest_distance_x = 0;
    int shortest_distance_y = 0;
    int whose_turn = 0;
    mapPoint* cell;
    //deminer* current_deminer = deminers[0];

    int** path = malloc(mapSize * mapSize * sizeof(int*)); //Allokerer array, der holder stien
    if (path == NULL) {
        printf("Allocation of path failed, exiting...\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < mapSize * mapSize; i++) {
        path[i] = malloc(2 * sizeof(int));
        if (path[i] == NULL) {
            printf("Allocation of path failed, exiting...\n");
            exit(EXIT_FAILURE);
        }
    }

    int path_length;

    while (amount_of_mines != 1) {
        printf("\033[0m");
        amount_of_mines = 0;
        shortest_distance_x = 0;
        shortest_distance_y = 0;
        shortest_distance = INT_MAX;
        for (int y = 0; y < mapSize; y++) {
            for (int x = 0; x < mapSize; x++) {
                cell = get_cell(map, mapSize, y, x);

                if (cell->point_value == MINE_ENUM) {
                    amount_of_mines++;

                    distance = bfs_find_distance(mapSize, map, deminers[whose_turn].x, deminers[whose_turn].y, x, y, path, &path_length);
                    if (distance == -1) {
                        printf("One or more mines couldn't be reached\n");
                        continue;
                    }
                    if (distance < shortest_distance) {
                        shortest_distance = distance;
                        shortest_distance_x = x;
                        shortest_distance_y = y;
                    }
                    printf("The distance is %d to mine X:%d, Y:%d\n", distance, x, y);
                }
            }
        }

        printf("The shortest distance is %d to mine X:%d, Y:%d, deminer %d moves.\n", shortest_distance, shortest_distance_x, shortest_distance_y, whose_turn + 1);

        //Efter den tætteste mine er fundet af køres bfs med mål kun mod den tætteset mine,
        //for at opdatere path til den korrekte, så ruten kan genskabes:
        reset_path(path, mapSize);
        bfs_find_distance(mapSize, map, deminers[whose_turn].x, deminers[whose_turn].y, shortest_distance_x, shortest_distance_y, path, &path_length);

        //Laver loop, der tilskriver ruten i mappet:
        for (int step = 0; step < shortest_distance; step++) {
            int x = path[step][0];
            int y = path[step][1];

            if (x < 0 || x >= mapSize || y < 0 || y >= mapSize) {
                printf("Error: Path coordinates out of bounds at step %d: (%d, %d)\n", step, x, y);
                exit(EXIT_FAILURE);
            }

            //Det ønskes ikke at overskrive miner, andre deminere og steder, der allerede er placeret explosives:
            if (map[y * mapSize + x].point_value != MINE_ENUM &&
                map[y * mapSize + x].point_value != DEMINER_ENUM &&
                map[y * mapSize + x].point_value != EXPLOSIVE_ENUM) {
                map[y * mapSize + x].point_value = PATH_ENUM;
            }
        }

        deminers[whose_turn].distance += shortest_distance;
        //printf("So far deminer 0 has walked %d\n", deminers[0].distance);
        deminers[whose_turn].x = shortest_distance_x; //Flytter demineren
        deminers[whose_turn].y = shortest_distance_y;

        if (whose_turn < amount_of_deminers - 1) {
            whose_turn++;
        } else {
            whose_turn = 0;
        }

        print_map(mapSize, map, deminers, amount_of_deminers);
        get_cell(map, mapSize, shortest_distance_y, shortest_distance_x)->point_value = EXPLOSIVE_ENUM;
        char choice;
        scanf(" %c", &choice);
    }
    for (int i = 0; i < amount_of_deminers; i++) {
        deminers[i].x = -1;
        deminers[i].y = -1;
    }
    print_map(mapSize, map, deminers, amount_of_deminers);
    free(path);
}


int find_shortest_path_distance_sorter(const void *ep1, const void *ep2) {
    return (int*) ep1 - (int*) ep2;
}