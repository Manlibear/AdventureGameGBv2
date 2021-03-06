#ifndef _MAP_LAYER_H
#define _MAP_LAYER_H
#define MAP_LAYERS_COUNT 2

#include <gb/gb.h>
#include <string.h>
#include "../res/tiles/overworld.h"
#include "../res/tiles/indoors.h"
#include "map_data.h"
#include "player_controller.h"
#include "map.h"
#include "screen.h"

typedef struct MapLayer
{
    const unsigned char walkable_tiles[25];
    const unsigned char infront_tiles[2];
    const unsigned char *tile_map;
    const unsigned char tile_map_bank;
    const unsigned char tile_map_length;
} MapLayer;

extern const struct MapLayer map_layers[MAP_LAYERS_COUNT];

char is_tile_walkable(UINT16 x, UINT16 y, unsigned char layer);
char is_on_travel_tile();
char is_tile_interactable();

#endif