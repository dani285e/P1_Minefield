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

enum point_value {
    CLEAR_ENUM,          // Represents an empty or clear space
    OBSTACLE_ENUM,       // Represents an obstacle (e.g., a tree or blockage)
    OBSTACLE_WALKABLE_ENUM,
    MINE_ENUM,           // Represents a mine
    EXPLOSIVE_ENUM,
    DEMINER_ENUM,


    PATH_ENUM,           // Represents a path
    LOWER_ELEVATION_ENUM,// Represents a cell with lower elevation (adjacent to a hill)
    LESSER_ELEVATION_ENUM,// Represents a cell with the lowest elevation
    HILL_ENUM,           // Represents a hill (highest elevation)
    BLAST_RADIUS_ENUM         // Represents the blast radius of a mine
};

static char point_value_name[11] = {'.', 'X', 'W', 'M', 'E', 'D', '*', 'L', 'l', 'H', 'B'};


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
