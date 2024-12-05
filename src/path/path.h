//
// Created by kaspe on 05-12-2024.
//

#ifndef PATH_H
#define PATH_H
#include "src/structs.h"
#include "src/map/map.h"
#include "src/blast_radius/blast_radius.h"
#include <stdio.h>
#include <stdlib.h>


Queue* create_queue();
void enqueue(Queue* queue, int x, int y, int distance);
int dequeue(Queue* queue, int* x, int* y, int* distance);
int is_empty(Queue* queue);
void free_queue(Queue* queue);

void find_shortest_path (int mapSize, mapPoint* map, int amount_of_deminers, Deminer* deminers);
void find_closest_mine(int* shortest_distance_x, int* shortest_distance_y, int* shortest_distance, int* shortest_distance_weight, int mapSize, mapPoint* map,
                        int whose_turn, Deminer* deminers, int* amount_of_mines, int** path, int* path_length, int* weight);


int bfs_find_distance(int mapsize, mapPoint* map, int start_x, int start_y, int target_x, int target_y, int** path, int* path_length, int* weight);
void reset_path(int** path, int mapsize);
void print_path(int shortest_distance, int** path, int mapSize, mapPoint* map);
void update_deminer(Deminer* deminers, int* whose_turn, int shortest_distance, int shortest_distance_x, int shortest_distance_y, int amount_of_deminers);

#endif //PATH_H
