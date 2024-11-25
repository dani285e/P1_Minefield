

#include "terrain.h"


/*
struct for terrain
terrain types update around the map
randomly generated
then translate struct map in the time for the terrain.ID = yes,
* --------------------*/


int terrain_function() {

int terrain_count = TERRAIN_COUNT; // Midlertidig antal
int terrain_x;
int terrain_y;
Area terrains_arr[terrain_count]; // Laver en array mines[mine_count] af structen Mines

for(int i = 0; i < terrain_count; i++) {  // Tæller op i et loop, hvor mange mine_x og mine_y værdier, der skal være samt hvor mange mineID der skal være
    terrain_x = i;
    terrain_y = i;
    terrains_arr[i].x = terrain_x; // Tilkobler arrayet med structen og giver værdien "x" værdien "mine_x"
    terrains_arr[i].y = terrain_y; // Samme som ovenover bare med y
    terrains_arr[i].TerrainID = i; // Samme som ovenover bare med mineID
}

hill_radius(hill_count, hills); // Kalder blast_radius funktionen
return 0;
}


Terrain terrain_coordinate(int y, int x, int id){
        Terrain terrain; // Definerer en blast ud fra structen Blast
        terrain.y = y; // Tildeler blast y værdien i structen Blast
        terrain.x = x; // Tildeler blast x værdien i structen Blast
        terrain.TerrainID = id; // Tildeler blast mineID i structen Blast
        return terrain;
}


Terrain terrain_radius(int terrain_count, Terrain * terrain) {
     *blast = malloc(sizeof(Hill) * hill_count * 7);
    if (hills == NULL) {
        printf("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    int hill_index = 0;  // Blast index er hvilket felt den er nået til. Den starter i felt 0

    for (int i = 0; i < hill_count; i++) {   // Den tæller, hvor mange miner der er. Den starter ved 0 og tæller op
        for (int j = 0; j < 7; j++) { // Den tæller, hvor mange felter i arrayet omrking minen, som skal kategoriseres som radius
            int temporary_y = hills[i].y; // Tilføjer temporary values for ikke at ændre i den originale struct
            int temporary_x = hills[i].x;
            blast[i] = hill_coordinate(temporary_y, temporary_x, hills[i].hillID);
            blast[hill_index] = hill_coordinate(temporary_y--, temporary_x, hills[i].hillID); // Under minen
            hill_index++; // Tæller op for hver gang den har været i en bestemt del af arrayet, så den ikke kategoriserer det samme felt 2 gange
            blast[hill_index] = hill_coordinate(temporary_y, temporary_x++, hills[i].hillID); // Til højre for minen
            hill_index++;
            blast[hill_index] = hill_coordinate(temporary_y++, temporary_x++, hills[i].hillID); // Højre skrå hjørne
            hill_index++;
            blast[hill_index] = hill_coordinate(temporary_y++, temporary_x, hills[i].hillID); // Over minen
            hill_index++;
            blast[hill_index] = hill_coordinate(temporary_y, temporary_x--, hills[i].hillID); // Til venstre for minen
            hill_index++;
            blast[hill_index] = hill_coordinate(temporary_y--, temporary_x--, hills[i].hillID); // Venstre nederste hjørne
        }
    }

    free(hills);
    return hills[0];
}

