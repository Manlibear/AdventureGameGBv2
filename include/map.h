#ifndef _MAP_H
#define _MAP_H

#include <gb/gb.h>
#include "player_controller.h"

#define SCR_LEFT (draw_target_x - 9)
#define SCR_RIGHT (draw_target_x + 10)
#define SCR_TOP (draw_target_y - 7)
#define SCR_BOTTOM (draw_target_y + 10)

#include "sprite.h"
#include "map_area.h"
#include "map_layer.h"
#include "screen.h"


extern const MapArea oob;
void redraw_map();
void draw_map_slice();
MapArea *get_area(UINT16 x, UINT16 y);
void determine_area(UINT16 x, UINT16 y);
MapArea *get_adjacent_area(UINT16 x, UINT16 y);

#endif