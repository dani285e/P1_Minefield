#include "src//deminers/deminers.h"
#include "src/path/path.h"
#include "src/map/map.h"
#include "src/path/start_point/start_point.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#define MINES 20

int main(void) {

    srand(time(NULL)); // Sætter rand seed

    mapPoint* map = NULL; // map er en pointer til mapPoint struct

    int mapSize = (rand()% 11) + 20; // mapSize bliver et random til mellem 20 og 30 inklusiv
    int amount_of_mines = 0; // amount_of_mines initialiseres, værdien ændres senere
    int quick_run = 2; // quick_run initialiseres, værdien ændres senere
    int amount_of_deminers = 0; // amount_of_deminers initialiseres, værdien ændres senere

    map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize); // Pladsen til map array allokeres

    Deminer* deminers = NULL; // deminers er en pointer til Deminer struct

    continue_check(); // Programmet stopper indtil det modtager bruger input
    create_map(mapSize, map, &amount_of_mines); // Mappet genereres

    initial_print_map(mapSize, map); // Mappet printes ud med clears, obstacles og mines

    user_input_deminers(mapSize, &amount_of_deminers); // Brugeren vælger hvor mange de-miners der skal bruges

    deminers = (Deminer*)malloc(sizeof(Deminer)*amount_of_deminers); // Pladsen til deminers array allokeres

    continue_check(); // Programmet stopper indtil det modtager bruger input
    print_map_info(mapSize, map, amount_of_deminers); // Map info udskrives

    continue_check(); // Programmet stopper indtil det modtager bruger input
    function_find_start_line(mapSize, map, deminers, amount_of_deminers); // Startline findes og starting points genereres

    print_map(mapSize, map, deminers, amount_of_deminers); // Mappet printes ud med clears, obstacles, mines og de-miners

    run_mode(&quick_run); // Brugeren vælger en run mode

    find_shortest_path(mapSize, map, amount_of_deminers, deminers, quick_run); // Resten af programmet køres her

    free(map); // Map array bliver free
    free(deminers); // Deminers array bliver free

    return 0;
}