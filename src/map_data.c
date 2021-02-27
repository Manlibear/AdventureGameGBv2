#pragma bank 2

#include "../include/map_data.h"

const struct LayerData layers_data[3] = {
    // overworld
    [0] = {
        .maps = {
            // pallet town
            [1] = {
                .travel_tiles = {
                    // player's house
                    [0] = {
                        .sourceX = 114,
                        .sourceY =  478,
                        .targetLayer = 0,
                        .targetX = 110,
                        .targetY = 201
                    }
                }
            }
        }
    }
};