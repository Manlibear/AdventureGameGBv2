#pragma bank 24
#include "rivals_house_data.h"

const struct TravelTile rivals_house_travel_tiles[TRAVEL_TILES_COUNT] = {
    // door out
    {
        .sourceX = 73,
        .sourceY = 465,
        .targetLayer = overworld_idx,
        .targetX = 130,
        .targetY = 479}};

const struct Interactable rivals_house_interactables[INTERACTABLE_COUNT] = {
    {0}
};