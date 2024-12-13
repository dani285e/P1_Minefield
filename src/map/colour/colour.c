#include "colour.h"

char point_value_color[11][10] = {
    "\033[0;32m",   //CLEAR_ENUM (Green)
    "\033[0;33m",   //OBSTACLE_ENUM (Yellow)
    "\033[0;36m",   //OBSTACLE_WALKABLE_ENUM (Cyan)
    "\033[0;31m",   //MINE_ENUM (Red)
    "\033[0;34m",   //EXPLOSIVE_ENUM (Blue)
    "\033[0m",      //DEMINER_ENUM (Default/No color)
    "\033[0m",      //PATH_ENUM (Default/No color)
    "\033[0m",      //LOWER_ELEVATION_ENUM (Default/No color)
    "\033[0m",      //LESSER_ELEVATION_ENUM (Default/No color)
    "\033[0m",      //HILL_ENUM (Default/No color)
    "\033[0;35m"    // Blast_Radius (Purple)
};