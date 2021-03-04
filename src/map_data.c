#include "../include/map_data.h"

#include "../data/pallet_town_data.h"
#include "../data/players_house_1f_data.h"
#include "../data/players_house_gf_data.h"
#include "../data/rivals_house_data.h"
#include "../data/oaks_lab_data.h"


const struct LayerData layers_data[3] = {
    [indoors_idx] = {
        .maps = {
            [players_house_1f_idx] = {
                .travel_tiles = &players_house_1f_travel_tiles
            },
            [players_house_gf_idx] = {
                .travel_tiles = &players_house_gf_travel_tiles
            },
            [rivals_house_idx] = {
                .travel_tiles = &rivals_house_travel_tiles
            },
            [oaks_lab_idx] = {
                .travel_tiles = &oaks_lab_travel_tiles
            }
        }
    },
    [overworld_idx] = {
        .maps = {
            [pallet_town_idx] = {
                .travel_tiles = &pallet_town_travel_tiles, 
                .interactables = &pallet_town_interactables
            }
        }
    },
};