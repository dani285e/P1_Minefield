#ifndef BLAST_RADIUS_H
#define BLAST_RADIUS_H
#include "src/map/map.h"

/// Opdaterer nærliggende celler blandt miner til BLAST_RADIUS_ENUM
/// @param mapSize Bruges som grænse i loops
/// @param map Bruges til get_cell() kald
void blast_radius(int mapSize, mapPoint* map);

#endif //BLAST_RADIUS_H
