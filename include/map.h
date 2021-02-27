#ifndef _MAP_H
#define _MAP_H

#include <gb/gb.h>
#include "player_controller.h"

#define SCR_LEFT (target_x - 9)
#define SCR_RIGHT (target_x + 10)
#define SCR_TOP (target_y - 7)
#define SCR_BOTTOM (target_y + 10)

#include "sprite.h"
#include "map_area.h"


extern const MapArea oob;
void redraw_map();
void draw_map_slice();
MapArea *get_area(UINT16 x, UINT16 y);

#endif