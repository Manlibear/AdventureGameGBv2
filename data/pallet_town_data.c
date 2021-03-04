#pragma bank 22
#include "pallet_town_data.h"

const struct TravelTile pallet_town_travel_tiles[TRAVEL_TILES_COUNT] = {
    // player's house
    {
        .sourceX = 114,
        .sourceY = 478,
        .targetLayer = indoors_idx,
        .targetX = 46,
        .targetY = 464},
    // rival's house
    {
        .sourceX = 130,
        .sourceY = 478,
        .targetLayer = indoors_idx,
        .targetX = 73,
        .targetY = 464},
    // oak's lab
    {
        .sourceX = 128,
        .sourceY = 490,
        .targetLayer = indoors_idx,
        .targetX = 77,
        .targetY = 498}};

const struct Interactable pallet_town_interactables[INTERACTABLE_COUNT] = {
    // sign near player's house
    {
        .text = "Player's house\\pointer",
        .x = 110,
        .y = 478
    },
    // sign near rival's house
    {
        .text = "Rival's house",
        .x = 126,
        .y = 478
    },
    // sign in the center of town
    {
        .text = "PALLET TOWN\\Shades of your\\journey await!",
        .x = 118,
        .y = 486
    },
    // sign outside Oak's Lab
    {
        .text = "Prof Oak's Pokemon\\Research Lab",
        .x = 130,
        .y = 494
    }
};