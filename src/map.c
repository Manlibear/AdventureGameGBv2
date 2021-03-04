#include "../include/map.h"
#include "../include/debug.h"

char i;
char j;
MapArea *tile_area = 0;
MapArea *current_area = 0;
MapArea *adj_area = 0;
const MapArea oob = {0};

unsigned char loaded_layer = 0;
unsigned char tile_load_buffer[22 * 20];
unsigned char oob_fill = 0x04;

void redraw_map()
{
    tile_area = get_area(target_x, target_y);

    if (tile_area->layer != loaded_layer)
    {
        position_layer = tile_area->layer;
        loaded_layer = tile_area->layer;

        SWITCH_ROM_MBC1(map_layers[tile_area->layer].tile_map_bank);
        set_bkg_data(1, map_layers[tile_area->layer].tile_map_length, map_layers[tile_area->layer].tile_map);
    }

    if (tile_area->bank != _current_bank)
    {
        SWITCH_ROM_MBC1(tile_area->bank);
    }

    wait_vbl_done();

    UINT16 tile_index;
    UINT16 target_tile;
    tile_area = get_area(target_x, target_y);
    for (i = -1; i < 19; i++)
    {
        for (j = -1; j < 21; j++)
        {
            if ((SCR_LEFT + j) >= tile_area->xs && (SCR_TOP + i) >= tile_area->ys && (SCR_LEFT + j) <= tile_area->xe && (SCR_TOP + i) <= tile_area->ye)
            {
                target_tile = SCR_LEFT + j + (tile_area->row_length * i);

                tile_index = target_tile - tile_area->xs + ((SCR_TOP - tile_area->ys) * tile_area->row_length);
                tile_load_buffer[(j + 1) + ((i + 1) * 22)] = tile_area->map_data[tile_index];
            }
            else
            {
                tile_load_buffer[(j + 1) + ((i + 1) * 22)] = oob_fill;
            }
        }
    }

    set_bkg_tiles(SCR_LEFT - 1 & 31, SCR_TOP - 1 & 31, 22, 20, tile_load_buffer);
}

void draw_map_slice()
{
    if (player.last_facing == FACE_NONE)
        return;

    UINT16 draw_edge;
    INT16 count = 0;

    if (player.last_facing == FACE_E || player.last_facing == FACE_W)
    {
        draw_edge = player.last_facing == FACE_E ? SCR_RIGHT + 1 : SCR_LEFT - 1;
        for (i = -1; i < 19; i++)
        {
            tile_area = get_adjacent_area(draw_edge, SCR_TOP + i);

            // maps are never stored in bank 0, so if this thinks it is then it's OOB
            if (tile_area->bank == 0)
            {
                tile_load_buffer[i + 1] = oob_fill;
            }
            else
            {
                if (tile_area->bank != _current_bank)
                {
                    SWITCH_ROM_MBC1(tile_area->bank);
                }

                tile_load_buffer[i + 1] = tile_area->map_data[(draw_edge + (tile_area->row_length * i)) - tile_area->xs + ((SCR_TOP - tile_area->ys) * tile_area->row_length)];
            }
        }

        set_bkg_tiles(draw_edge & 31, SCR_TOP - 1 & 31, 1, 20, tile_load_buffer);
    }

    if (player.last_facing == FACE_N || player.last_facing == FACE_S)
    {
        draw_edge = player.last_facing == FACE_S ? SCR_BOTTOM + 1 : SCR_TOP - 1;
        for (i = -1; i < 21; i++)
        {
            tile_area = get_adjacent_area(SCR_LEFT + i, draw_edge);

            if (tile_area->bank == 0)
            {
                tile_load_buffer[i + 1] = oob_fill;
            }
            else
            {
                if (tile_area->bank != _current_bank)
                {
                    SWITCH_ROM_MBC1(tile_area->bank);
                }

                tile_load_buffer[i + 1] = tile_area->map_data[((draw_edge - tile_area->ys) * tile_area->row_length) + (i + SCR_LEFT - tile_area->xs)];
            }
        }

        set_bkg_tiles(SCR_LEFT - 1 & 31, draw_edge & 31, 22, 1, tile_load_buffer);
    }
}

void determine_area(UINT16 x, UINT16 y)
{
    tile_area = current_area = get_area(x, y);
}

MapArea *get_area(UINT16 x, UINT16 y)
{
    // if we've already got a map_area...
    if (tile_area != 0)
    {
        // ... check if it's the one we need
        if (position_layer == tile_area->layer && x >= tile_area->xs && y >= tile_area->ys && x <= tile_area->xe && y <= tile_area->ye)
        {
            current_area = tile_area;
            return tile_area;
        }
    }

    // cache miss, time to go find the correct area
    for (i = 0; i < map_area_count; i++)
    {
        if (position_layer == areas[i].layer && x >= areas[i].xs && y >= areas[i].ys && x <= areas[i].xe && y <= areas[i].ye)
        {
            current_area = &areas[i];
            return &areas[i];
        }
    }

    // out of bounds tile, MapArea->bank will be 0, avoid random bank switching from un-init memory and will render a blank tile
    return &oob;
}

MapArea *get_adjacent_area(UINT16 x, UINT16 y)
{
    if (position_layer == current_area->layer && x >= current_area->xs && y >= current_area->ys && x <= current_area->xe && y <= current_area->ye)
        return current_area;

    for (int a = 0; a < 4; a++)
    {
        adj_area = &areas[current_area->adjacents[a]];

        if (position_layer == adj_area->layer && x >= adj_area->xs && y >= adj_area->ys && x <= adj_area->xe && y <= adj_area->ye)
        {
            current_area = adj_area;
            return adj_area;
        }
    }

    return &oob;
}