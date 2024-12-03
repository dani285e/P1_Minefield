//
// Created by Danie on 22-11-2024.
//

#ifndef STRUCTS_H
#define STRUCTS_H
typedef struct QueueNode {
    int x;
    int y;
    int distance;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;


typedef struct {
    int x;
    int y;
    int distance;
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
    EXPLOSIVE_ENUM,
    DEMINER_ENUM,
    LOWER_ELEVATION_ENUM,// Represents a cell with lower elevation (adjacent to a hill)
    LESSER_ELEVATION_ENUM// Represents a cell with the lowest elevation
};

static char point_value_name[9] = {'C', 'O', 'M', 'P', 'H', 'E', 'D', 'L', 'l'}; // Corresponding characters


typedef struct {
    int point_value_x;
    int point_value_y;
    enum point_value point_value;
} mapPoint;

typedef struct {
    int start_point_x;
    int start_point_y;
} startpoint;


#endif //STRUCTS_H
