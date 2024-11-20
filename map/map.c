//
// Created by Danie on 20-11-2024.
//

#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#define MINES 20

#define OBSTACLE_NONE 0
#define OBSTACLE_TREE 1
#define OBSTACLE_HILL 2
#define OBSTACLE_STONE 3

// Funktion der genererer en arena
void createMap(int* mapSize, char** map) {
    char* cell; // Cell er en pointer til en char
    int mapSizetemp = (rand()% 20) + 10;;
    *mapSize = mapSizetemp;
    //printf("Please enter a map size\n");
    //scanf("%d", &mapSizetemp);
    printf("Map size is: %d\n", mapSizetemp);
    *map = (char*)malloc(mapSizetemp*mapSizetemp*sizeof(char));

    for (int y = 0; y < mapSizetemp; y++) { // Nested for loop der kører igennem alle pladser i 2D arrayet
        for (int x = 0; x < mapSizetemp; x++) {
            int outcome = (rand() % MINES) + 1;
            cell = getCell(*map, mapSizetemp, y, x); // Sætter cell pointeren lig med den pointer vi får tilbage af getCell funktionen
            if(outcome == 1) {
                *cell = 'M';
            } else if (outcome > 1 && outcome < 5) {
                *cell = 'X';
            } else {
                *cell = 'O';
            }
        }
    }
}

char* getCell(char* map, int mapSize, int y, int x) { // getCell funktionen der returnerer en pointer til en char
    char* cell = map + mapSize * x + y;
    return cell;
}

void printMap(char* map, int mapSize, Deminer deminer) { // printMap funktionen udskriver alle elementer i 2D arrayet
    int mineCounter = 0;
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            if (y == deminer.y && x == deminer.x) {
                blue();
                printf("%2c", 'P');
                reset();
            } else {
                if (*getCell(map, mapSize, y, x) == 'M') {
                    red();
                    printf("%2c", *getCell(map, mapSize, y, x));
                    reset();
                    mineCounter++;
                } else if (*getCell(map, mapSize, y, x) == 'X') {
                    yellow();
                    printf("%2c", *getCell(map, mapSize, y, x));
                    reset();
                } else {
                    green();
                    printf("%2c", *getCell(map, mapSize, y, x)); // Udskriver den værdi der ligger på hver plads i 2D arrayet
                    reset();
                }
            }
        }
        printf("\n");
    }

    printf("\n\n");
    printf("There is a total of %d mines there needs to be cleared\n", mineCounter);
    printf("They are located at the following points\n");
    int counter = 0;
    for(int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            if (*getCell(map, mapSize, y, x) == 'M') {
                counter = counter + 1;
                printf("%-2d Mine: X = %-2d, Y = %d\n", counter, x, y);
            }
        }
    }
}
