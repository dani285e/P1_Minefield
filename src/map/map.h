#ifndef MAP_H
#define MAP_H


#include <stdio.h>
#include <stdlib.h>
#include "src/path/start_point/start_point.h"
#include "src/map/colour/colour.h"
#include "src/structs.h"

/// Giver en pointer til en celle, ud fra mappet, mapsize og cellens x- og y-værdi.
/// @param map Bruges til indeksering for celle-indeks
/// @param mapSize Bruges til indeksering for celle-indeks
/// @param y Bruges til indeksering for celle-indeks
/// @param x Bruges til indeksering for celle-indeks
/// @return Returnerer en pointer til en celle.
mapPoint* get_cell(mapPoint* map, int mapSize, int y, int x);

/// Laver et map i mapPoint arrayet: map[].
/// @param mapSize Bruges som grænse i loops.
/// @param map Bruges til get_cell kald.
/// @param amount_of_mines Bruges til at gemme antallet af miner.
void create_map(int mapSize, mapPoint* map, int* amount_of_mines);

/// Printer mappet ud fra ENUM-værdier
/// @param mapSize Bruges som grænse i loops.
/// @param map Bruges til get_cell kald.
/// @param deminers Bruges til at tjekke om, der er deminers på cellen.
/// @param amount_of_deminers Bruges som grænse for at loope gennem deminernes lokationer.
void print_map(int mapSize, mapPoint* map, Deminer* deminers, int amount_of_deminers);

/// Printer info omkring mappet. (Antal miner, placeringer, antal deminers)
/// @param mapSize
/// @param map
/// @param amount_of_deminers
void print_map_info(int mapSize, mapPoint* map, int amount_of_deminers);


/// Printer mappet uden deminers
/// @param mapSize
/// @param map
void initial_print_map(int mapSize, mapPoint* map);

/// Forhindrer programmet i et kører helt færdigt med det samme det køres
void continue_check();

/// Tager input til antal deminers, men giver også et anbefalet antal baseret på størrelsen af mappet
/// @param mapSize Bruges til anbefaling
/// @param amount_of_deminers Assigner antal deminers til variablen.
void user_input_deminers(int mapSize, int* amount_of_deminers);

/// Prompter brugeren for run mode 1 for quick 0 for normal.
/// @param quick_run Returneres gennem parameter
void run_mode(int* quick_run);
#endif //MAP_H