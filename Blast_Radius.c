#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define BLAST 1
#define MINE_COUNT 5
#define TRUE 1
#define FALSE 0
#define ACTIVE_MINERS 5

// En funktion der skal være aktiv i programmet, hvis der er 2 eller flere mineryddere
// En funktion der bestemmer, hvad blast radius er

// En funktion der sørger for, at 2 deminers ALDRIG kan være indenfor en bestemt blast radius
typedef struct Mines {
    int x;
    int y;
    int mineID; // Dette skal bruges til at fjerne radius efter at minen er clearet
} Mines; // Et struct med, hvad minerne indeholder. De indeholder en x- og y koordinat samt et mineID

typedef struct Blast {
    int x;
    int y;
    int mineID;
} Blast; // Et struct med, hvad blast radius indeholder. Det indeholder en x- og y koordinat samt et mineID

Blast blast_radius(int active_miners, int *true_false, int mine_count, Mines * mines);
Blast add_koordinat(int y, int x, int id);
void radius_of_explosion(int n);

int main(void) {
    int mine_count = MINE_COUNT; // Midlertidig antal
    int true_flag = TRUE;
    int mine_x;
    int mine_y;
    Mines mines[mine_count]; // Laver en array mines[mine_count] af structen Mines
    for(int i = 0; i < mine_count; i++) {  // Tæller op i et loop, hvor mange mine_x og mine_y værdier, der skal være samt hvor mange mineID der skal være
        mine_x = i;
        mine_y = i;
        mines[i].x = mine_x; // Tilkobler arrayet med structen og giver værdien "x" værdien "mine_x"
        mines[i].y = mine_y; // Samme som ovenover bare med y
        mines[i].mineID = i; // Samme som ovenover bare med mineID
    }
    blast_radius(ACTIVE_MINERS, &true_flag, mine_count, mines); // Kalder blast_radius funktionen
    return 0;
}


Blast blast_radius(int active_miners, int *true_false, int mine_count, Mines * mines) {
    Blast *blast = malloc(sizeof(Blast) * mine_count * 9);
    if (blast == NULL) {
        printf("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    if (active_miners > 1) {
        // Funktion der er aktiv, hvis der er 2 eller flere deminers
         *true_false = TRUE;
    }
    if (active_miners < 2) {
        *true_false = FALSE;
    }
    int blast_index = 0;  // Blast index er hvilket felt den er nået til. Den starter i felt 0
    while(*true_false == TRUE) { // Imens der er mere end 1 deminer
        for (int i = 0; i < mine_count; i++) {   // Den tæller, hvor mange miner der er. Den starter ved 0 og tæller op
            for (int j = 0; j < 9; j++) { // Den tæller, hvor mange felter i arrayet omrking minen, som skal kategoriseres som radius
                int temporary_y = mines[i].y; // Tilføjer temporary values for ikke at ændre i den originale struct
                int temporary_x = mines[i].x;
                blast[i] = add_koordinat(temporary_y, temporary_x, mines[i].mineID);
                blast[blast_index] = add_koordinat(temporary_y--, temporary_x, mines[i].mineID); // Under minen
                blast_index++; // Tæller op for hver gang den har været i en bestemt del af arrayet, så den ikke kategoriserer det samme felt 2 gange
                blast[blast_index] = add_koordinat(temporary_y--, temporary_x++, mines[i].mineID); // Skråt for under minen
                blast_index++;
                blast[blast_index] = add_koordinat(temporary_y, temporary_x++, mines[i].mineID); // Til højre for minen
                blast_index++;
                blast[blast_index] = add_koordinat(temporary_y++, temporary_x++, mines[i].mineID); // Højre skrå hjørne
                blast_index++;
                blast[blast_index] = add_koordinat(temporary_y++, temporary_x, mines[i].mineID); // Over minen
                blast_index++;
                blast[blast_index] = add_koordinat(temporary_y++, temporary_x--, mines[i].mineID); // Venstre skrå hjørne
                blast_index++;
                blast[blast_index] = add_koordinat(temporary_y, temporary_x--, mines[i].mineID); // Til venstre for minen
                blast_index++;
                blast[blast_index] = add_koordinat(temporary_y--, temporary_x--, mines[i].mineID); // Venstre nederste hjørne
            }
        }
    }
    free(blast);
    return blast[0];
}
Blast add_koordinat(int y, int x, int id) {
    Blast blast; // Definerer en blast ud fra structen Blast
    blast.y = y; // Tildeler blast y værdien i structen Blast
    blast.x = x; // Tildeler blast x værdien i structen Blast
    blast.mineID = id; // Tildeler blast mineID i structen Blast
    return blast;
}