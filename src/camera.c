#include "../include/camera.h"

#define SCREEN_MID_X (SCX_REG + 9 * 8)
#define SCREEN_MID_Y (SCY_REG + 7 * 8)

char move_x = 0;
char move_y = 0;

char adjust_x_0 = 0;
char adjust_y_0 = 0;
char adjust_x_1 = 0;
char adjust_y_1 = 0;

char move_time = 0;
char frames_since_update = 0;
char move_amount = 0;
char needs_redraw = 0;
char move_per_step= 16;

void update_camera()
{
    needs_redraw = 0;
    player.was_moving = player.is_moving;
    if (!player.is_moving && player.facing != FACE_NONE)
    {
        draw_target_x = target_x = position_x;
        draw_target_y = target_y = position_y;

        switch (player.facing)
        {
        case FACE_N:
            target_y -= 2;
            draw_target_y -= 1;
            player.is_moving = 1;
            break;
        case FACE_S:
            target_y += 2;
            draw_target_y += 1;
            player.is_moving = 1;
            break;
        case FACE_E:
            target_x += 2;
            draw_target_x += 1;
            player.is_moving = 1;
            break;
        case FACE_W:
            target_x -= 2;
            draw_target_x -= 1;
            player.is_moving = 1;
            break;
        }

        if (!is_tile_walkable(target_x, target_y, position_layer))
        {
            draw_target_x = target_x = position_x;
            draw_target_y = target_y = position_y;
            player.is_moving = 0;
            player.was_moving = 0;
            return;
        }

        if (player.is_moving)
        {
            move_x = move_y = 0;

            if (position_x != target_x)
            {
                move_x = target_x > position_x ? 1 : -1;
                move_amount = move_per_step;
            }

            if (position_y != target_y)
            {
                move_y = target_y > position_y ? 1 : -1;
                move_amount = move_per_step;
            }

            needs_redraw = 1;
            has_travelled = 0;
        }
    }

    if (player.is_moving && move_amount > 0)
    {
        if(move_amount == 8)
        {
            needs_redraw = 1;
            draw_target_x = target_x;
            draw_target_y = target_y;
        }

        if (frames_since_update >= move_time)
        {
            frames_since_update = 0;
            scroll_bkg(move_x, move_y);
            move_amount--;
        }
        else
        {
            frames_since_update++;
        }
    }

    if (move_amount == 0)
    {
        position_x = target_x;
        position_y = target_y;
        player.is_moving = 0;
    }
}