// #include <math.h>
// #include <stdbool.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <time.h>
//
// #define BLAST 1
// #define MINE_COUNT 5
// #define TRUE 1
// #define FALSE 0
// #define MINES 20
//
// #define OBSTACLE_NONE 0
// #define OBSTACLE_TREE 1
// #define OBSTACLE_HILL 2
// #define OBSTACLE_STONE 3
//
// enum point_value {
//     CLEAR_ENUM, OBSTACLE_ENUM, MINE_ENUM, BlastRadius // Har tilføjet blast radius til denne struct
// };
// char point_value_name[4] = {'O', 'X', 'M', 'B'}; // Har tilføjet B til denne char array
//
// typedef struct mapPoint {
//     int point_value_x;
//     int point_value_y;
//     enum point_value point_value;
// } mapPoint;
//
// mapPoint* get_cell(mapPoint* map, int mapSize, int y, int x);
// void create_map(int mapSize, mapPoint* map);
// void print_map(int mapSize, mapPoint* map);
// void check_a_point(int mapSize, mapPoint* map);
// void red();
// void green();
// void reset();
// void yellow();
// void blue();
// void blast_radius(int mapSize, mapPoint* map); // Denne funktion er tilføjet for at få blast raduius
//
// int main(void) {
//     srand(time(NULL));
//     mapPoint* map = NULL;
//     int mapSize = (rand() % 20) + 10;
//     map = (mapPoint*)malloc(sizeof(mapPoint) * mapSize * mapSize);
//
//     // Generate the map
//     create_map(mapSize, map);
//     print_map(mapSize, map);
//
//     // Mark the blast radius on the map
//     blast_radius(mapSize, map);
//     printf("\nUpdated Map After Blast Radius:\n"); // Printer et nyt map efter blast radius
//     print_map(mapSize, map);
//
//     // Check specific points
//     check_a_point(mapSize, map);
//
//     free(map);
//     map = NULL;
//
//     return 0;
// }
//
// mapPoint* get_cell(mapPoint* map, int mapSize, int y, int x) {
//     return map + mapSize * y + x;
// }
//
// void create_map(int mapSize, mapPoint* map) {
//     mapPoint* cell;
//     for (int y = 0; y < mapSize; y++) {
//         for (int x = 0; x < mapSize; x++) {
//             cell = get_cell(map, mapSize, y, x);
//             int outcome = rand() % 10; // Randomize terrain
//             if (outcome < 1) {
//                 cell->point_value = MINE_ENUM;
//             } else if (outcome < 4) {
//                 cell->point_value = OBSTACLE_ENUM;
//             } else {
//                 cell->point_value = CLEAR_ENUM;
//             }
//             cell->point_value_x = x;
//             cell->point_value_y = y;
//         }
//     }
// }
//
// void print_map(int mapSize, mapPoint* map) {
//     for (int y = 0; y < mapSize; y++) {
//         for (int x = 0; x < mapSize; x++) {
//             mapPoint* cell = get_cell(map, mapSize, y, x);
//
//             if (cell->point_value == MINE_ENUM) {
//                 red();
//             } else if (cell->point_value == OBSTACLE_ENUM) {
//                 yellow();
//             } else if (cell->point_value == BlastRadius) { // Har tilføjet blast radius til print_map
//                 blue();
//             } else {
//                 green();
//             }
//
//             printf("%3c", point_value_name[cell->point_value]);
//             reset();
//         }
//         printf("\n");
//     }
// }
//
// void check_a_point(int mapSize, mapPoint* map) {
//     int current_x, current_y;
//     printf("\nCheck the value at a certain point by entering an X and Y coordinate:\n");
//     scanf("%d %d", &current_x, &current_y);
//
//     if (current_x < 0 || current_x >= mapSize || current_y < 0 || current_y >= mapSize) {
//         printf("Point is outside of the map\n");
//     } else {
//         mapPoint* cell = get_cell(map, mapSize, current_y, current_x);
//         printf("At point X:%d, Y:%d, there is %c\n",
//                cell->point_value_x,
//                cell->point_value_y,
//                point_value_name[cell->point_value]);
//     }
// }
//
// void blast_radius(int mapSize, mapPoint* map) {
//     for (int y = 0; y < mapSize; y++) { // For loop som kører rundt til alle x værdier
//         for (int x = 0; x < mapSize; x++) { // For loop som kører rundt til alle y værdier
//             mapPoint* cell = get_cell(map, mapSize, y, x); // Kalder structen mapPoint og giver den navnet cell
//
//             if (cell->point_value == MINE_ENUM) { // Hvis det er en mine
//                 for (int dy = -1; dy <= 1; dy++) { // Kører for loopet til de omkringliggende arrays om minerne for y
//                     for (int dx = -1; dx <= 1; dx++) { // for x
//                         int new_y = y + dy;
//                         int new_x = x + dx;
//
//                         // Sikre at den er inden for mappet
//                         if (new_y >= 0 && new_y < mapSize && new_x >= 0 && new_x < mapSize) {
//                             mapPoint* surrounding_cell = get_cell(map, mapSize, new_y, new_x);
//
//                             // Kun opdaterer celler der er clear
//                             if (surrounding_cell->point_value == CLEAR_ENUM) {
//                                 surrounding_cell->point_value = BlastRadius;
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }
//
// void red() {
//     printf("\033[0;31m");
// }
//
// void green() {
//     printf("\033[0;32m");
// }
//
// void reset() {
//     printf("\033[0m");
// }
//
// void yellow() {
//     printf("\033[0;33m");
// }
//
// void blue() { // Tilføjet blå for at gøre blast radius sejere
//     printf("\033[0;34m");
// }
