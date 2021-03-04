#include "..\include\main.h"

void main()
{
    init();

    while (1)
    {
        wait_vbl_done();
        handle_player_input();
        if (!window_showing)
        {
            // check to see if we're interacting with a tile
            if (is_interacting && is_tile_interactable())
            {
                continue;
            }

            // player movement
            update_camera();
            handle_animation(&player);

            if (!player.is_moving && !has_travelled && is_on_travel_tile())
            {
                // travel tile
                has_travelled = 1;
                fade_out_black();
                move_bkg((SCR_LEFT * 8) & 255, ((SCR_TOP * 8)) & 255);
                redraw_map();
                fade_in();
            }
            else if (needs_redraw)
            {
                draw_map_slice();
            }
        }
        else if (is_interacting)
        {
            if (text_window_offset > 0)
            {
                text_window_offset = show_text_window(text_window_text, text_window_length, text_window_bank, text_window_offset);
            }
            else
            {
                hide_window();
            }
        }
    }
}

void init()
{
    cpu_fast();

    SPRITES_8x16;

    SWITCH_RAM_MBC1(1);
    set_sprite_data(0, 4, player_sprites);
    set_sprite_tile(1, 3);
    set_sprite_palette(0, 1, spritePalette);
    set_bkg_palette(0, 3, bkgPalette);
    // set_sprite_prop(0, 0);

    player.sprite_index = 0;
    player.tile_index = 0;
    player.anim_state = 0;
    player.facing = FACE_S;
    player.last_facing = FACE_S;
    player.x = (9 * 8) + 8;
    player.y = (7 * 8) + 16;
    player.frame_length = player.frames_since_update = 8;

    position_x = target_x = draw_target_x = 118;
    target_y = draw_target_y = position_y = 480;
    position_layer = 1;

    determine_area(position_x, position_y);

    OBP0_REG = 0xE0;
    OBP1_REG = 0xE4;

    move_bkg((position_x - 9) * 8, (position_y - 7) * 8);

    move_sprite(0, player.x, player.y);
    move_sprite(1, player.x + 8, player.y);

    SWITCH_ROM_MBC1(overworldBank);
    set_bkg_data(1, overworld_length, overworld);

    redraw_map();

    SHOW_SPRITES;
    SHOW_BKG;
}