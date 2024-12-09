//
// Created by kaspe on 05-12-2024.
//

#ifndef PATH_H
#define PATH_H
#include "src/structs.h"
#include "src/map/map.h"
#include "src/blast_radius/blast_radius.h"
#include <stdio.h>
#include <stdlib.h>

/// Allokerer hukommelse til queue-struktur. Initialiserer front og back til NULL, da køen starter tom.
/// Queue-strukturen har to pointere: front & rear, start/slut af kø.
/// @return Returnerer en pointer til køen
Queue* create_queue();

/// Allokerer hukommelse til en ny QueueNode. Initialiserer nodens datafelter (x, y, distance).
/// Sætter nodens næste node til NULL, da dette element nu er det sidste i køen.
/// Er køen tom sættes front og rear til at pege på den næste nye node, ellers sættes den nuværende
/// rear->next til at pege på den nye node, og rear-noden bliver sat til den nye node.
/// @param queue Bruger køen
/// @param x x-værdi for punktet, der skal queues
/// @param y y-værdi for punktet, der skal queues
/// @param distance holder styr på, hvor langt, der er hen til punktet.
void enqueue(Queue* queue, int x, int y, int distance);

/// Fjerner det forreste element i køen og returnerer dens data. Sætter front-noden til at være den næste i køen.
/// @param queue Bruger køen.
/// @param x tager x, y og distance som pointer for at kunne tilskrive disse værdier, og derved dequeue elementet.
/// @param y 
/// @param distance 
/// @return 1 for vellykket, 0 hvis køen er tom
int dequeue(Queue* queue, int* x, int* y, int* distance);

/// Tjekker om køen er tom.
/// @param queue bruger køen.
/// @return 1 hvis køen er tom, 0 hvis tom.
int is_empty(Queue* queue);

/// Frigører al hukommelse brugt af køen. Itererer gennem hver node i køen via en pointer current, frigør hver enkelte
/// nodes hukommelse én efter én. Til sidst frigøres queue-strukturen.
/// @param queue Bruger køen til at frigøre hukommelse.
void free_queue(Queue* queue);

/// Finder og printer den korteste rute for hver deminer hen til den tætteste mine.
/// @param mapSize Bruger mapSize som grænse i bl.a. loops.
/// @param map Bruger mappet til at tjekke for miner.
/// @param amount_of_deminers Bruger antallet af deminers, så BFS-algoritmen og mappet kan opdateres tilsvarende
/// @param deminers Bruger deminer-arrayet for at holde styr på deminernes lokation.
void find_shortest_path (int mapSize, mapPoint* map, int amount_of_deminers, Deminer* deminers, int quick_run);

/// Finder den mine, der er tættest på whose_turn-demineren ved at udregne afstanden fra demineren hen til alle miner.
/// @param shortest_distance_x Tages som pointer for at assigne x-værdien på den tætteste mine.
/// @param shortest_distance_y Tages som pointer for at assigne y-værdien på den tætteste mine.
/// @param shortest_distance Tages som pointer for at assigne distancen til den tætteste mine.
/// @param mapSize Bruges som grænse til loops.
/// @param map Bruges til at tjekke felter.
/// @param whose_turn Holder styr på hvis/hvilken tur/deminer det er.
/// @param deminers Holder deminernes lokation.
/// @param amount_of_mines Bruges til at tælle og returnere antal miner.
/// @param path Gemmer stien, der bliver gået af BFS.
/// @param path_length Gemmer længden på stien, der bliver gået.
/// @param weight Holder vægten for stien
void find_closest_mine(int* shortest_distance_x, int* shortest_distance_y, int* shortest_distance, int* shortest_distance_weight, int mapSize, mapPoint* map,
                        int whose_turn, Deminer* deminers, int* amount_of_mines, int** path, int* path_length, int* weight);

/// BFS (Breadth-First-Search) Finder den korteste afstand fra et startpunkt til et slutpunkt, mens den undgår forhindringer.
/// @param mapsize Bruges som grænse i loops.
/// @param map Bruges til at tjekke cellers værdi.
/// @param start_x Startpositionens x-værdi, ofte givet ved deminer[whose_turn].x
/// @param start_y Startpositionens x-værdi, ofte givet ved deminer[whose_turn].y
/// @param target_x Mål-positionens x-værdi
/// @param target_y Mål-positionens y-værdi
/// @param path 2D-array, der holder stien, der gås af BFS.
/// @param path_length Holder længden af stien, der bruges til print.
/// @param weight Holder vægten for stien
/// @return Returnerer den udregnede afstand.
int bfs_find_distance(int mapsize, mapPoint* map, int start_x, int start_y, int target_x, int target_y, int** path, int* path_length, int* weight);

/// Nulstiller alle stiens værdier til -1.
/// @param path Bruger stien, for at nulstille den.
/// @param mapsize Bruger mapsize som grænse til loop.
void reset_path(int** path, int mapsize);

/// Indskriver stien i mappet.
/// @param path_length Bruger stiens længde som grænse i loop.
/// @param path Bruger path-array for x- og y-værdier til stien.
/// @param mapSize Bruger mapSize til kontrol af punkter, og indeksering af map[y * mapSize + x]
/// @param map Indskriver stien i mappet.
/// @param deminers Bruges til at addere tid til demineren.
/// @param whose_turn Bruges til at addere tid til den rigtige deminer.
/// @param time Holder styr på tiden, for hver enkelt rute.
void print_path(int shortest_distance, int** path, int mapSize, mapPoint* map, Deminer* deminers, int whose_turn, int* time);

/// Opdaterer deminernes lokation og, hvis tur det er til at rykke.
/// @param deminers Bruger deminers-arrayet til at tillægge den allerede-gået distance og ændre deminerens lokation.
/// @param whose_turn Bruges til at ændre den rigtige deminer og bruges til at ændre, hvis tur det er.
/// @param shortest_distance Tillægges den enkelte deminers totale distance gået.
/// @param shortest_distance_x Bruges som deminerens nye lokation-x
/// @param shortest_distance_y Bruges som deminerens nye lokation-y
/// @param amount_of_deminers Bruges som grænse til ændring af tur loop.
void update_deminer(Deminer* deminers, int* whose_turn, int shortest_distance, int shortest_distance_x, int shortest_distance_y, int amount_of_deminers);

#endif //PATH_H
