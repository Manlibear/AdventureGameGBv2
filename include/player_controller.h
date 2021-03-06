#ifndef _PLAYER_CONTROLLER_H
#define _PLAYER_CONTROLLER_H

#include <gb/gb.h>
#include "sprite.h"
#include "debug.h"

void handle_player_input();

extern UINT16 position_x;
extern UINT16 position_y;
extern unsigned char position_layer;

extern unsigned char has_travelled;
extern char is_interacting;

extern UINT16 target_x;
extern UINT16 target_y;
extern UINT16 draw_target_x;
extern UINT16 draw_target_y;


#endif