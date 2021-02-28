#pragma bank 2

#include "../include/map_data.h"



const struct LayerData layers_data[3] = {
    [overworld_idx] = {
        .maps = {
            [pallet_town_idx] = {
                .travel_tiles = {
                    // player's house
                    [0] = {
                        .sourceX = 114,
                        .sourceY =  478,
                        .targetLayer = indoors_idx,
                        .targetX = 47,
                        .targetY = 464
                    }
                }
            }
        }
    },
    [indoors_idx] = {
        .maps = {
            [players_house_1f_idx] = {
                .travel_tiles = {
                    // stairs down
                    [0] = {
                        .sourceX = 56,
                        .sourceY =  483,
                        .targetLayer = indoors_idx,
                        .targetX = 56,
                        .targetY = 452
                    }
                }
            },
            [players_house_gf_idx] = {
                .travel_tiles = {
                    // stairs up
                    [0] = {
                        .sourceX = 56,
                        .sourceY =  452,
                        .targetLayer = indoors_idx,
                        .targetX = 56,
                        .targetY = 483
                    },
                    // door out
                    [1] = {
                        .sourceX = 47,
                        .sourceY =  465,
                        .targetLayer = overworld_idx,
                        .targetX = 114,
                        .targetY = 479
                    }
                }
            }
        }
    }
};