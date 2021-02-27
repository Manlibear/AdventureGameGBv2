#include "../include/sprite.h"

#include <stdio.h>

struct Sprite player;
struct Sprite sprites[20];
char flip_x;

void set_sprite_frame(Sprite *spr, UINT8 tile)
{
    set_sprite_tile(spr->sprite_index, tile);
    set_sprite_tile(spr->sprite_index + 1, tile + 2);
}

void handle_animation(Sprite *spr)
{

    if (spr->is_moving && spr->facing != FACE_NONE && !spr->was_moving)
    {
        // we are moving for the first time
        spr->frames_since_update = 0;
        spr->anim_state = 1 - spr->anim_state;
        spr->last_facing = spr->facing;
        spr->flip_x = (spr->last_facing == FACE_N || spr->last_facing == FACE_S) && spr->anim_state > 0;

        set_sprite_frame(spr, spr->tile_index + (4 * (spr->facing > 2 ? 2 : spr->facing)) + 12);

        if (spr->flip_x || spr->last_facing == FACE_E)
        {
            set_sprite_prop(spr->sprite_index, S_FLIPX);
            set_sprite_prop(spr->sprite_index + 1, S_FLIPX);
            move_sprite(spr->sprite_index, spr->x + 8, spr->y);
            move_sprite(spr->sprite_index + 1, spr->x, spr->y);
        }
        else
        {
            set_sprite_prop(spr->sprite_index, 0x00);
            set_sprite_prop(spr->sprite_index + 1, 0x00);
            move_sprite(spr->sprite_index, spr->x, spr->y);
            move_sprite(spr->sprite_index + 1, spr->x + 8, spr->y);
        }
    }

    if (spr->was_moving)
    {
        // we were moving
        if (spr->frames_since_update >= spr->frame_length)
        {
            // and we need an update
            spr->frames_since_update = 0;
            set_sprite_frame(spr, spr->tile_index + (4 * (spr->last_facing > 2 ? 2 : spr->last_facing)));
        }
        else
        {
            // not due an update
            spr->frames_since_update++;
        }
    }

    if (!spr->is_moving && !spr->was_moving && spr->facing != FACE_NONE && spr->facing != spr->last_facing)
    {
        spr->last_facing = spr->facing;
        // looks like we collided with something, snap to face that direction
        set_sprite_frame(spr, spr->tile_index + (4 * (spr->last_facing > 2 ? 2 : spr->last_facing)));
        spr->flip_x = 0;
        if (spr->last_facing == FACE_E)
        {
            set_sprite_prop(spr->sprite_index, S_FLIPX);
            set_sprite_prop(spr->sprite_index + 1, S_FLIPX);
            move_sprite(spr->sprite_index, spr->x + 8, spr->y);
            move_sprite(spr->sprite_index + 1, spr->x, spr->y);
        }
        else
        {
            set_sprite_prop(spr->sprite_index, 0x00);
            set_sprite_prop(spr->sprite_index + 1, 0x00);
            move_sprite(spr->sprite_index, spr->x, spr->y);
            move_sprite(spr->sprite_index + 1, spr->x + 8, spr->y);
        }
    }
}
