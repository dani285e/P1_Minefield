#include "path.h"

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

/*
 * Funktion til at finde og navigere med den korteste rute for deminere, for at rydde miner på et givet kort.
 * Deminerne arbejder i en rotation og finder den nærmeste mine til dem og navigere mod den ved hjælp af BFS.
*/

void find_shortest_path (int mapSize, mapPoint* map, int amount_of_deminers, Deminer* deminers, int quick_run) {
    int amount_of_mines = -1;
    int shortest_distance = INT_MAX;
    int shortest_distance_x = 0;
    int shortest_distance_y = 0;
    int shortest_distance_weight = INT_MAX;
    int whose_turn = 0;
    int time = 0;
    mapPoint* cell;

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

    int path_length = 0;
    int weight = 0;

    while (amount_of_mines != 1) {
        printf("\033[0m");

        //Finder den tætteste mine for deminerens tur, opdaterer shortest_distance x, y og amount_of_mines:
        find_closest_mine(&shortest_distance_x, &shortest_distance_y, &shortest_distance, &shortest_distance_weight ,mapSize, map, whose_turn,
                            deminers, &amount_of_mines, path, &path_length, &weight);

        //Nulstiller tid for deminers
        //Efter den tætteste mine er fundet af køres bfs med mål kun mod den tætteste mine,
        //for at opdatere path til den korrekte, så ruten kan genskabes:
        reset_path(path, mapSize); //Resetter path array til -1
        bfs_find_distance(mapSize, map, deminers[whose_turn].x, deminers[whose_turn].y, shortest_distance_x, shortest_distance_y, path, &path_length, &weight);
        print_path(shortest_distance, path, mapSize, map, deminers, whose_turn, &time); //Printer pathen og opdaterer tid for deminers:
        if (quick_run == 0) {
            printf("The shortest distance to a mine is %d\nThe mine is located at X:%d, Y:%d\nDe-miner %d moves\nIt takes %d minutes to reach the mine and plant an explosive\n", path_length, shortest_distance_x, shortest_distance_y, whose_turn + 1, time);
        }

        //Opdaterer deminerens placering, og hvis tur det er, så samme deminer ikke også går næste gang:
        update_deminer(deminers, &whose_turn, shortest_distance, shortest_distance_x, shortest_distance_y, amount_of_deminers);

        //Printer mappet:
        if (quick_run == 0) {
            print_map(mapSize, map, deminers, amount_of_deminers);
        }

        //Planter explosive på minens placering
        get_cell(map, mapSize, shortest_distance_y, shortest_distance_x)->point_value = EXPLOSIVE_ENUM;

        // Vil kun køres hvis brugeren har valgt regular run mode
        if (quick_run == 0) {
            continue_check();
        }
    }

    //Er alle miner nået flyttes deminerne ud af griddet:
    for (int i = 0; i < amount_of_deminers; i++) {
        deminers[i].x = -1;
        deminers[i].y = -1;
    }

    //Printer mappet en sidste gang uden deminers:
    blast_radius(mapSize, map);
    print_map(mapSize, map, deminers, amount_of_deminers);
    free(path);

    printf("\033[0m");
    printf("\nAll mines have been reached!\n");
    int total_distance = 0;
    int total_time = 0;
    for (int i = 0; i < amount_of_deminers; i++) {
        printf("Total distance walked for de-miner %d is %d, it took %d minutes\n", i+1,  deminers[i].distance, deminers[i].time_taken);
        total_distance += deminers[i].distance;
        total_time += deminers[i].time_taken;
    }
    printf("Total distance walked all de-miners is %d\n", total_distance);
    printf("Total time spent by all de-miners is %d minutes\n", total_time);
}


void find_closest_mine(int* shortest_distance_x, int* shortest_distance_y, int* shortest_distance, int* shortest_distance_weight, int mapSize, mapPoint* map,
                        int whose_turn, Deminer* deminers, int* amount_of_mines, int** path, int* path_length, int* weight) {
    *weight = 0;
    *amount_of_mines = 0;
    *shortest_distance_x = 0;
    *shortest_distance_y = 0;
    *shortest_distance_weight = INT_MAX;
    *shortest_distance = INT_MAX;

    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            mapPoint* cell = get_cell(map, mapSize, y, x);

            if (cell->point_value == MINE_ENUM) {
                *amount_of_mines += 1;

                int distance = bfs_find_distance(mapSize, map, deminers[whose_turn].x, deminers[whose_turn].y, x, y, path, path_length, weight);
                if (distance == -1) {
                    printf("One or more mines couldn't be reached\n");
                    continue;
                }
                // Er den nuværende vægt mindre end den tidligere så opdateres følgende værdier
                if (*weight < *shortest_distance_weight) {
                    *shortest_distance_weight = *weight;
                    *shortest_distance = distance;
                    *shortest_distance_x = x;
                    *shortest_distance_y = y;
                }
            }
        }
    }
}


/*
 * Beregner den korteste rute fra startpositionen til målpositionen på et kvadratisk kort
 * ved hjælp af breadth-first search (BFS) algoritmen. Stien og dens længde gemmes i
 * de angivne variabler, og den totale vægt af stien beregnes.
*/
int bfs_find_distance(int mapsize, mapPoint* map, int start_x, int start_y, int target_x, int target_y, int** path, int* path_length, int* weight) {
    *weight = 0;
    int local_weight = 0;
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
            local_weight = dist;
            //Tilbagetracker for at finde ruten:
            int current_x = target_x, current_y = target_y; // Start fra målets koordinater

            for (int step = dist; step >= 0; step--) {
                // Find forgængeren fra `prev`
                mapPoint previous_cell = prev[current_y][current_x];


                if (current_x != -1 || current_y != -1) {
                    path[step][0] = current_x;
                    path[step][1] = current_y;

                    int current_point_value = get_cell(map, mapsize, current_y, current_x)->point_value;

                    if (current_point_value == OBSTACLE_WALKABLE_ENUM) {
                        local_weight += 3;
                    }

                    current_x = previous_cell.point_value_x;   // Kolonnen (x-koordinat)
                    current_y = previous_cell.point_value_y;   // Rækken (y-koordinat)
                }

            }
            *weight = local_weight;

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

/*
 * Nulstiller værdierne i path-arrayet. Hver position i path sættes til -1 for at indikere, at der ikke er nogen sti til den pågældende position.
 * Dette bruges til at nulstille path-arrayet så det efterfølgende kan beregne efterfølgende 'path' uden gamle værdier.
*/
void reset_path(int** path, int mapsize) {
    //Resetter path-arrayet:
    for (int i = 0; i < mapsize * mapsize; i++) {
        for (int j = 0; j < 2; j++) {
            path[i][j] = -1;
        }
    }
}


/*
 * Denne funktion tager en sti og markerer den på et kort, ved at ændre point_value for hver celle på stien.
 * Den kontrollerer også, om koordinaterne er indenfor kortets grænser og om cellen allerede er et minefelt, deminers sted eller et eksplosivt område.
*/
void print_path(int shortest_distance, int** path, int mapSize, mapPoint* map, Deminer* deminers, int whose_turn, int* time) {
    //Laver loop, der tilskriver ruten i mappet:
    *time = 0;
    for (int step = 0; step <= shortest_distance; step++) {
        int x = path[step][0];
        int y = path[step][1];

        if (x < 0 || x >= mapSize || y < 0 || y >= mapSize) {
            printf("Error: Path coordinates out of bounds at step %d: (%d, %d)\n", step, x, y);
            exit(EXIT_FAILURE);
        }

        int current_point_value = get_cell(map, mapSize, y, x)->point_value;
        if (step == 0 && current_point_value == MINE_ENUM) {
            *time = 5;
        }
        if (step != 0) {
            switch (current_point_value) {
                case CLEAR_ENUM:
                    *time += 1;
                    deminers[whose_turn].time_taken += 1;
                    break;
                case PATH_ENUM:
                    *time += 1;
                    deminers[whose_turn].time_taken += 1;
                case OBSTACLE_WALKABLE_ENUM:
                    *time += 2;
                    deminers[whose_turn].time_taken += 2;
                    break;
                case MINE_ENUM:
                    *time += 5;
                    deminers[whose_turn].time_taken += 5;
                    break;
            }
        }

        //Det ønskes ikke at overskrive miner, andre deminere og steder, der allerede er placeret explosives:
        if (map[y * mapSize + x].point_value != MINE_ENUM &&
            map[y * mapSize + x].point_value != DEMINER_ENUM &&
            map[y * mapSize + x].point_value != EXPLOSIVE_ENUM) {
            map[y * mapSize + x].point_value = PATH_ENUM;
            }
    }
}

//Funktionen opgdaterer deminers lokation, distance og tur.
void update_deminer(Deminer* deminers, int* whose_turn, int shortest_distance, int shortest_distance_x, int shortest_distance_y, int amount_of_deminers) {
    deminers[*whose_turn].distance += shortest_distance;
    //printf("So far deminer 0 has walked %d\n", deminers[0].distance);
    deminers[*whose_turn].x = shortest_distance_x; //Flytter demineren
    deminers[*whose_turn].y = shortest_distance_y;

    if (*whose_turn < amount_of_deminers - 1) {
        *whose_turn += 1;
    } else {
        *whose_turn = 0;
    }
}