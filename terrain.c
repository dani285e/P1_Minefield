

#include "terrain.h"
#include "map/map.h"


// Funktion, der opdatere mappet
void update_map (char* map, int mapSize) {
    // Loop, der kører igennem arrayet(map)
    for (int x = 0; x < mapSize; x++) {
        for (int y = 0; y < mapSize; y++) {
            // Kalder funktionen update_sorrounding_cells, hvis det enkelte element/celle er B
            if (*getCell(map, mapSize, y, x) == 'B') {
                update_Surrounding_Cells(map, mapSize, y, x, LESS_ELEVATION_SYMBOL);
            }
        }
    }
}

void update_Surrounding_Cells(char* map, int mapSize, int y, int x, char newVal) {
    int directions[8][2] = { // De 8 retninger omkring en celle
        {-1, -1}, {-1, 0},{-1, 1}, // Øverst venstre, op, øverst højre
        {0, -1},            {0, 1},  // Venstre, højre
        {1, -1}, {1, 0}, {1, 1}    // Nederst venstre, ned, nederst højre
    };

    // Kører igennem for hvert eneste koordinat rundt om 'B'
    for (int i = 0; i < 8; i++) {

        // Giver et tal til begge int typer
        int ny = y + directions[i][0];
        int nx = x + directions[i][1];

        // Tjek om naboen er inden for kortets grænser
        if (ny >= 0 && ny < mapSize && nx >= 0 && nx < mapSize) {
            // Tager cellen i arrayet for de omkringliggende elementer
            char* cell = getCell(map, mapSize, ny, nx);
            // Overskriver de omkringliggende elementer til ny værdi, hvis ikke det er char værdierne 'B' og 'M'
            if (*cell != 'B') { // Undgå at overskrive en bakke
                *cell = newVal;
            }
        }
    }
}


// Funktion der genererer en arena
void create_elevation_map(int mapSize, char** elevation_map) {
    char* cell; // Cell er en pointer til en char
    *elevation_map = (char*)malloc(mapSize*mapSize*sizeof(char));

    for (int y = 0; y < mapSize; y++) {
        // Nested for loop der kører igennem alle pladser i 2D arrayet
        for (int x = 0; x < mapSize; x++) {
            int outcome = (rand() % mapSize) + 1;
            cell = getCell(*elevation_map, mapSize, y, x); // Sætter cell pointeren lig med den pointer vi får tilbage af getCell funktionen
            if(outcome == 1) {
                *cell = HILL_SYMBOL;
            } else { //only path symbol for as big as map size
                for (int i = 0; i < mapSize; ++i) {
                    *cell = BLANK_SYMBOL;
                }
            }
        }
    }
}
