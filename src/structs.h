//
// Created by Danie on 22-11-2024.
//

#ifndef STRUCTS_H
#define STRUCTS_H


typedef struct deminer{
    int id;
    int x;
    int y;
} Deminer;

typedef struct Map {
    int x;
    int y;
    char obstacle;
}map;

enum point_value {
    CLEAR_ENUM,          // Represents an empty or clear space
    OBSTACLE_ENUM,       // Represents an obstacle (e.g., a tree or blockage)
    MINE_ENUM,           // Represents a mine
    PATH_ENUM,           // Represents a path
    HILL_ENUM,           // Represents a hill (highest elevation)
    LOWER_ELEVATION_ENUM,// Represents a cell with lower elevation (adjacent to a hill)
    LESSER_ELEVATION_ENUM// Represents a cell with the lowest elevation
};

static char point_value_name[7] = {'C', 'O', 'M', 'P', 'H', 'L', 'l'}; // Corresponding characters


typedef struct {
    int point_value_x;
    int point_value_y;
    enum point_value point_value;
} mapPoint;

#endif //STRUCTS_H
