//
// Created by Danie on 20-11-2024.
//

#include "colour.h"

void red() {
    printf("\033[0;31m");
}
void green() {
    printf("\033[0;32m");
}
void yellow() {
    printf("\033[0;33m");
}
void blue() {
    printf("\033[0;34m");
}

void reset() {
    printf("\033[0m");
}

char point_value_color[9][10] = {
    "\033[0;32m",   //CLEAR_ENUM
    "\033[0;33m",   //OBSTACLE_ENUM
    "\033[0;31m",   //MINE_ENUM
    "\033[0m",      //PATH_ENUM
    "\033[0m",      //HILL_ENUM
    "\033[0;34m",   //EXPLOSIVE_ENUM
    "\033[0m",      //DEMINER_ENUM
    "\033[0m",      //LOWER_ELEVATION_ENUM
    "\033[0m",      //LESSER_ELEVATION_ENUM
};
