

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

/// Printer info omkring mappet. (Antal miner, placeringer)
/// @param mapSize
/// @param map
void print_map_info(int mapSize, mapPoint* map);


// Bruges første gang mappet udskrives så vi får et map uden deminers
void initial_print_map(int mapSize, mapPoint* map);

// Forhindrer programmet i et kører helt færdigt med det samme det køres
void continue_check(int start);


#endif //MAP_H
