#pragma bank 2

#include "../include/map_data.h"

const struct LayerData layers_data[3] = {
    // overworld
    [0] = {
        .maps = {
            // pallet town
            [11] = {
                .travel_tiles = {
                    // player's house
                    [0] = {
                        .sourceX = 114,
                        .sourceY =  478,
                        .targetLayer = 1,
                        .targetX = 46,
                        .targetY = 464
                    }
                }
            }
        }
    },
    // indoors
    [1] = {
        .maps = {
            // player's house 1f
            [0] = {
                .travel_tiles = {
                    // stairs down
                    [0] = {
                        .sourceX = 56,
                        .sourceY =  483,
                        .targetLayer = 1,
                        .targetX = 56,
                        .targetY = 452
                    }
                }
            },
            // player's house gf
            [1] = {
                .travel_tiles = {
                    // stairs up
                    [0] = {
                        .sourceX = 56,
                        .sourceY =  452,
                        .targetLayer = 1,
                        .targetX = 56,
                        .targetY = 483
                    }
                }
            }
        }
    }
};