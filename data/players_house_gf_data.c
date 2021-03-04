#pragma bank 23
#include "players_house_gf_data.h"

const struct TravelTile players_house_gf_travel_tiles[TRAVEL_TILES_COUNT] = {
    // stairs up
    {
        .sourceX = 56,
        .sourceY = 452,
        .targetLayer = indoors_idx,
        .targetX = 56,
        .targetY = 483},
    // door out
    {
        .sourceX = 47,
        .sourceY = 466,
        .targetLayer = overworld_idx,
        .targetX = 114,
        .targetY = 480
    }
};

const struct Interactable players_house_gf_interactables[INTERACTABLE_COUNT];