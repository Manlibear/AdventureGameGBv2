#pragma bank 2

#include "../include/map_data.h"



const struct LayerData layers_data[3] = {
    [overworld_idx] = {
        .maps = {
            [pallet_town_idx] = {
                .travel_tiles = {
                    // player's house
                    {
                        .sourceX = 114,
                        .sourceY =  478,
                        .targetLayer = indoors_idx,
                        .targetX = 47,
                        .targetY = 464
                    },
                    // rival's house
                    {
                        .sourceX = 130,
                        .sourceY =  478,
                        .targetLayer = indoors_idx,
                        .targetX = 73,
                        .targetY = 464
                    },
                    // oak's lab
                    {
                        .sourceX = 128,
                        .sourceY =  490,
                        .targetLayer = indoors_idx,
                        .targetX = 77,
                        .targetY = 498
                    }
                },
                .interactables = {
                    // sign near player's house
                    {
                        .text = "Player's house",
                        .x = 110,
                        .y = 479
                    },
                    // sign near rival's house
                    {
                        .text = "Rival's house",
                        .x = 126,
                        .y = 479
                    },
                    // sign in the center of town
                    {
                        .text = "PALLET TOWN\\Shades of your\\journey await!",
                        .x = 118,
                        .y = 487
                    },
                    // sign outside Oak's Lab
                    {
                        .text = "Prof Oak's Pokemon\\Research Lab",
                        .x = 130,
                        .y = 495
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
                    {
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
                    {
                        .sourceX = 56,
                        .sourceY =  452,
                        .targetLayer = indoors_idx,
                        .targetX = 56,
                        .targetY = 483
                    },
                    // door out
                    {
                        .sourceX = 47,
                        .sourceY =  465,
                        .targetLayer = overworld_idx,
                        .targetX = 114,
                        .targetY = 479
                    }
                }
            },
            [rivals_house_idx] = {
                .travel_tiles = {
                    // door out
                    {
                        .sourceX = 73,
                        .sourceY =  465,
                        .targetLayer = overworld_idx,
                        .targetX = 130,
                        .targetY = 479
                    }
                }
            },
            [oaks_lab_idx] = {
                .travel_tiles = {
                    // door out
                    {
                        .sourceX = 77,
                        .sourceY =  499,
                        .targetLayer = overworld_idx,
                        .targetX = 128,
                        .targetY = 491
                    }
                }
            }
        }
    }
};