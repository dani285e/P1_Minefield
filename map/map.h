//
// Created by Danie on 20-11-2024.
//

#ifndef MAP_H
#define MAP_H

void createMap(int* mapSize, char** map);
char* getCell(char* map, int mapSize, int y, int x);
void printMap(char* map, int mapSize, struct deminer);

typedef struct Map {
    int x;
    int y;
    int obstacle;
}map;

#endif //MAP_H
