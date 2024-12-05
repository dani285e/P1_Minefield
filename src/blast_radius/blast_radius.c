#include <src/map/map.h>

void blast_radius(int mapSize, mapPoint* map) {
    for (int y = 0; y < mapSize; y++) { // For loop som kører rundt til alle x værdier
        for (int x = 0; x < mapSize; x++) { // For loop som kører rundt til alle y værdier
            mapPoint* cell = get_cell(map, mapSize, y, x); // Kalder structen mapPoint og giver den navnet cell

            if (cell->point_value == EXPLOSIVE_ENUM) { // Hvis det er en mine
                for (int dy = -1; dy <= 1; dy++) { // Kører for loopet til de omkringliggende arrays om minerne for y
                    for (int dx = -1; dx <= 1; dx++) { // for x
                        int new_y = y + dy;
                        int new_x = x + dx;

                        // Sikre at den er inden for mappet
                        if (new_y >= 0 && new_y < mapSize && new_x >= 0 && new_x < mapSize) {
                            mapPoint* surrounding_cell = get_cell(map, mapSize, new_y, new_x);

                            // Kun opdaterer celler der er clear
                            if (surrounding_cell->point_value == CLEAR_ENUM ||
                                surrounding_cell->point_value == OBSTACLE_WALKABLE_ENUM ||
                                surrounding_cell->point_value == OBSTACLE_ENUM) {
                                surrounding_cell->point_value = BLAST_RADIUS_ENUM;
                                }
                        }
                    }
                }
            }
        }
    }
}
