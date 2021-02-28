#include "../include/map.h"
#include "../include/debug.h"

char i;
char j;
MapArea *tile_area = 0;
const MapArea oob = {0};

unsigned char loaded_layer = 0;
unsigned char tile_load_buffer[22 * 20];
unsigned char oob_fill = 0x68;

void redraw_map()
{
    tile_area = get_area(target_x, target_y);

    if (tile_area->layer != loaded_layer)
    {
        position_layer = tile_area->layer;
        loaded_layer = tile_area->layer;

        SWITCH_ROM_MBC1(map_layers[tile_area->layer].tile_map_bank);
        set_bkg_data(104, map_layers[tile_area->layer].tile_map_length, map_layers[tile_area->layer].tile_map);
    }

    if (tile_area->bank != _current_bank)
    {
        SWITCH_ROM_MBC1(tile_area->bank);
    }

    wait_vbl_done();

    UINT16 tile_index;
    UINT16 target_tile;
    BGB_MESSAGE_FMT(dmb, "redraw");
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

    UINT16 tile_index;
    UINT16 target_tile;
    char i;
    UINT16 draw_edge;
    INT16 count = 0;

    if (player.last_facing == FACE_E || player.last_facing == FACE_W)
    {
        draw_edge = player.last_facing == FACE_E ? SCR_RIGHT + 1 : SCR_LEFT - 1;
        for (i = -1; i < 19; i++)
        {
            tile_area = get_area(draw_edge, SCR_TOP + i);

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

                target_tile = draw_edge + (tile_area->row_length * i);

                tile_index = target_tile - tile_area->xs + ((SCR_TOP - tile_area->ys) * tile_area->row_length);
                tile_load_buffer[i + 1] = tile_area->map_data[tile_index];
            }
        }

        set_bkg_tiles(draw_edge & 31, SCR_TOP - 1 & 31, 1, 20, tile_load_buffer);
    }

    if (player.last_facing == FACE_N || player.last_facing == FACE_S)
    {
        draw_edge = player.last_facing == FACE_S ? SCR_BOTTOM + 1 : SCR_TOP - 1;
        for (i = -1; i < 21; i++)
        {
            tile_area = get_area(SCR_LEFT + i, draw_edge);

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

                target_tile = (draw_edge - tile_area->ys) * tile_area->row_length;
                tile_index = target_tile + (i + SCR_LEFT - tile_area->xs);
                tile_load_buffer[i + 1] = tile_area->map_data[tile_index];
            }
        }

        set_bkg_tiles(SCR_LEFT - 1 & 31, draw_edge & 31, 22, 1, tile_load_buffer);
    }
}

MapArea *get_area(UINT16 x, UINT16 y)
{
    // if we've already got a map_area...
    if (tile_area != 0)
    {
        // ... check if it's the one we need
        if (position_layer == tile_area->layer && x >= tile_area->xs && y >= tile_area->ys && x <= tile_area->xe && y <= tile_area->ye)
            return tile_area;
    }

    // cache miss, time to go find the correct area
    for (i = 0; i < map_area_count; i++)
    {
        if (position_layer == areas[i].layer && x >= areas[i].xs && y >= areas[i].ys && x <= areas[i].xe && y <= areas[i].ye)
        {
            return &areas[i];
        }
    }

    // out of bounds tile, MapArea->bank will be 0, avoid random bank switching from un-init memory and will render a blank tile
    return &oob;
}
