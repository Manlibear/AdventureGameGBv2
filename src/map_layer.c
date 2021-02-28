#include "../include/map_layer.h"

unsigned char tile_check_buffer[1];

const struct MapLayer map_layers[MAP_LAYERS_COUNT] = {
    [overworld_idx] = {
        .tile_map = overworld,
        .tile_map_length = overworld_length,
        .tile_map_bank = overworldBank,
        .walkable_tiles = {
            15,
            0x00,
            0x68,
            0x6B,
            0x6E,
            0x6F,
            0x6B,
            0xC0,
            0xC1,
            0xC6,
            0x8C,
            0x8D,
            0x8F,
            0x95,
            0xA1,
            0xBB,
        }
    },
    [indoors_idx] = {
        .tile_map = indoors,
        .tile_map_length = indoors_length,
        .tile_map_bank = indoorsBank,
        .walkable_tiles = {
            21,
            0x87,
            0x88,
            0x96,
            0xD3,
            0xD4,
            0x85,
            0x86,
            0x99,
            0x9A,
            0x9B,
            0x9C,
            0xAA,
            0xA7,
            0xB8,
            0xB9,
            0xBA,
            0xBB,
            0xCC,
            0xCD,
            0xCE,
            0xCF,

        }
    }
};

char is_tile_walkable(UINT16 x, UINT16 y, unsigned char layer)
{
    get_bkg_tiles(x & 31, y & 31, 1, 1, tile_check_buffer);

    for (int i = 1; i <= map_layers[layer].walkable_tiles[0]; i++)
    {
        if (map_layers[layer].walkable_tiles[i] == tile_check_buffer[0])
            return 1;
    }

    return 0;
}

char is_on_travel_tile()
{
    SWITCH_ROM_MBC1(map_dataBank);
    MapArea *ma = get_area(position_x, position_y);
    TravelTile *tts = layers_data[position_layer].maps[ma->area_index].travel_tiles;

    for (int i = 0; i < TRAVEL_TILES_COUNT; i++)
    {
        if (position_x == tts[i].sourceX && position_y == tts[i].sourceY)
        {
            position_x = target_x = tts[i].targetX;
            position_y = target_y = tts[i].targetY;
            position_layer = tts[i].targetLayer;
            return 1;
        }
    }

    return 0;
}