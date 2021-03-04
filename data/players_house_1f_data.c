#pragma bank 24
#include "players_house_1f_data.h"

const struct TravelTile players_house_1f_travel_tiles[TRAVEL_TILES_COUNT] = {
    // stairs down
    {
        .sourceX = 56,
        .sourceY = 483,
        .targetLayer = indoors_idx,
        .targetX = 56,
        .targetY = 452
    }
};

const struct Interactable players_house_1f_interactables[INTERACTABLE_COUNT];