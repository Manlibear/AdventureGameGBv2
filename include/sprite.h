#ifndef _SPRITE_H
#define _SPRITE_H

#include <gb/gb.h>

#define FACE_S 0
#define FACE_N 1
#define FACE_E 2
#define FACE_W 3
#define FACE_NONE -1

typedef struct Sprite
{
    UINT16 x;
    UINT16 y;
    unsigned char sprite_index;
    unsigned char tile_index;
    char facing;
    char last_facing;
    char is_moving;
    char was_moving;
    char flip_x;
    unsigned char anim_state;
    unsigned char frame_length;
    unsigned char frames_since_update;
} Sprite;

extern struct Sprite player;
extern struct Sprite sprites[20];

void handle_animation(Sprite *spr);

#endif