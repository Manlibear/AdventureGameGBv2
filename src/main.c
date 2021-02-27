#include "..\include\main.h"

unsigned char btn;

void main()
{
    init();

    while (1)
    {
        wait_vbl_done();
        handle_player_input();
        update_camera();
        handle_animation(&player);
        if (needs_redraw)
        {
            if (is_on_travel_tile())
            {
                fade_out_black();
                move_bkg(((target_x - 9) * 8), ((target_y - 7) * 8) + 8);
                redraw_map();
                fade_in();
            }
            else
            {
                draw_map_slice();
            }
        }
    }
}

void init()
{
    SPRITES_8x16;

    SWITCH_RAM_MBC1(1);
    set_sprite_data(0, 24, player_sprites);
    player.sprite_index = 0;
    player.tile_index = 0;
    player.anim_state = 0;
    player.facing = FACE_S;
    player.last_facing = FACE_S;
    player.x = (9 * 8) + 8;
    player.y = (7 * 8) + 16;
    player.frame_length = player.frames_since_update = 3;

    position_x = 114;
    target_x = 114;
    position_y = 479;
    target_y = 479;
    position_layer = 0;

    OBP0_REG = 0xE0;
    OBP1_REG = 0xE4;

    move_bkg((position_x - 9) * 8, (position_y - 7) * 8);

    move_sprite(0, player.x, player.y);
    move_sprite(1, player.x + 8, player.y);

    SWITCH_ROM_MBC1(overworldBank);
    set_bkg_data(104, overworld_length, overworld);

    redraw_map();

    SHOW_SPRITES;
    SHOW_BKG;
}