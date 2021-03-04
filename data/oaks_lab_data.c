#pragma bank 25
#include "oaks_lab_data.h"


const struct TravelTile oaks_lab_travel_tiles[TRAVEL_TILES_COUNT] = {
    // door out
    {
        .sourceX = 77,
        .sourceY = 499,
        .targetLayer = overworld_idx,
        .targetX = 128,
        .targetY = 491}};

const struct Interactable oaks_lab_interactables[INTERACTABLE_COUNT] = {
    {0}
};