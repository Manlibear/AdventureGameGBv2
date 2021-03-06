#include "../include/player_controller.h"

unsigned char has_travelled = 0;
char is_interacting;
char allow_interact = 1;

unsigned char position_layer = 0;
UINT16 position_x = 0;
UINT16 position_y = 0;
UINT16 target_x = 0;
UINT16 target_y = 0;
UINT16 draw_target_x = 0;
UINT16 draw_target_y = 0;

void handle_player_input()
{
    is_interacting = 0;

    switch (joypad())
    {
    case J_UP:
        player.facing = FACE_N;
        break;
    case J_DOWN:
        player.facing = FACE_S;
        break;
    case J_LEFT:
        player.facing = FACE_W;
        break;
    case J_RIGHT:
        player.facing = FACE_E;
        break;
    case J_A:
        if (allow_interact){
            allow_interact = 0;
            is_interacting = 1;
        }
        break;
        
    default:
        player.facing = FACE_NONE;
        allow_interact = 1;
    }
}