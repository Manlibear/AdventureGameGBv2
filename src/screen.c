#include "../include/screen.h"

#define FADE_STEPS 4

char fade_delay = 6;

void fade_out_black()
{
    for (int i = 1; i != FADE_STEPS; ++i)
    {
        // 0xFFE4 is 11'11 11'11 11'10 01'00
        // (i << 1) is i*2
        // each iteration the number gets shifted by 2 bits to the right
        // each two bit pair represents a color on DMG
        // BGP_REG is 8 bit and upper 8 bit will be discarded on cast
        // i=0 would be 11'10 01'00
        // i=1 is 11'11 10'01 etc.
        BGP_REG = (0xFFE4 >> (i << 1));
        OBP0_REG = (0xFFE4 >> (i << 1));
        for (int j = 0; j < fade_delay; j++)
            wait_vbl_done();
    }
}

void fade_in()
{
    for (int i = FADE_STEPS; i >= 0; --i)
    {
        // 0xFFE4 is 11'11 11'11 11'10 01'00
        // 0xFFE0 is 11'11 11'11 11'11 00'00 as the sprites use a different palette
        // (i << 1) is i*2
        // each iteration the number gets shifted by 2 bits to the right
        // each two bit pair represents a color on DMG
        // BGP_REG is 8 bit and upper 8 bit will be discarded on cast
        // i=0 would be 11'10 01'00
        // i=1 is 11'11 10'01 etc.
        BGP_REG = (0xFFE4 >> (i << 1));
        OBP0_REG = (0xFFE0 >> (i << 1));
        for (int j = 0; j < fade_delay; j++)
            wait_vbl_done();
    }
}