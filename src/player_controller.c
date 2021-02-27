#include "../include/player_controller.h"

UINT16 position_x = 0;
UINT16 position_y = 0;
unsigned char position_layer = 0;

UINT16 target_x = 0;
UINT16 target_y = 0;


void handle_player_input()
{
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

    case J_SELECT:
        BGB_print_xy();
        break;

    default:
        player.facing = FACE_NONE;
    }
}