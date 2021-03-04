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
            0x01,
            0x04,
            0x07,
            0x08,
            0x1E,
            0x1D,
            0x25,
            0x26,
            0x2E,
            0x3A,
            0x53,
            0x54,
            0x5B,
            0x5C,
        }},
    [indoors_idx] = {.tile_map = indoors, .tile_map_length = indoors_length, .tile_map_bank = indoorsBank, .walkable_tiles = {
                                                                                                               24,
                                                                                                               0x78,
                                                                                                               0x85,
                                                                                                               0x86,
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

                                                                                                           }}};

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
    MapArea *ma = get_adjacent_area(position_x, position_y);
    SWITCH_ROM_MBC1(ma->bank);
    TravelTile (*tts)[TRAVEL_TILES_COUNT] = layers_data[position_layer].maps[ma->area_index].travel_tiles;

    for (int i = 0; i < TRAVEL_TILES_COUNT; i++)
    {
        if (position_x == (*tts)[i].sourceX && position_y == (*tts)[i].sourceY)
        {
            position_x = target_x = draw_target_x = (*tts)[i].targetX;
            position_y = target_y = draw_target_y = (*tts)[i].targetY;
            position_layer = (*tts)[i].targetLayer;
            return 1;
        }
    }

    return 0;
}

char is_tile_interactable()
{
    MapArea *ma = get_area(position_x, position_y);
    SWITCH_ROM_MBC1(ma->bank);
    Interactable (*ints)[INTERACTABLE_COUNT] = layers_data[position_layer].maps[ma->area_index].interactables;

    UINT16 int_target_x = position_x;
    UINT16 int_target_y = position_y;

    switch (player.last_facing)
    {
    case FACE_E:
        int_target_x += 2;
        break;

    case FACE_W:
        int_target_x -= 2;
        break;

    case FACE_N:
        int_target_y -= 2;
        break;

    case FACE_S:
        int_target_y += 2;
        break;
    }

    for (int i = 0; i < INTERACTABLE_COUNT; i++)
    {
        if (int_target_x == (*ints)[i].x && int_target_y == (*ints)[i].y)
        {
            // display message on screen
            text_window_offset = show_text_window((*ints)[i].text, strlen((*ints)[i].text), ma->bank, 0);
            return 1;
        }
    }

    return 0;
}