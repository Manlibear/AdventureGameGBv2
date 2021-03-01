#include "../include/screen.h"
#include "../include/debug.h"

#define FADE_STEPS 4

char fade_delay = 6;
char window_showing = 0;
int text_window_offset = 0;
int text_window_length = 0;
unsigned char text_window_bank = 0;
unsigned char *text_window_text;

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

void hide_window()
{
    HIDE_WIN;
    window_showing = 0;
}

int show_text_window(unsigned char *text, int length, unsigned char text_bank, int offset)
{
    move_win(7, 112); // 7 because default pos is actually -7,0

    SWITCH_ROM_MBC1(ui_tilesBank);
    set_win_data(0x5F, ui_tiles_count, ui_tiles);

    SWITCH_ROM_MBC1(ui_mapBank);
    set_win_tiles(0, 0, 20, 4, ui_map);

    SWITCH_ROM_MBC1(fontBank);
    set_win_data(0, font_length, font);

    SWITCH_ROM_MBC1(text_bank);

    text_window_text = text;
    text_window_length = length;
    text_window_bank = text_bank;

    unsigned char adjusted;
    int cur_x = 1;
    int cur_y = 1;
    int max_x = 18;
    char empty_space = 0x00;
    char return_position = 0;
    SHOW_WIN;
    window_showing = 1;

    BGB_MESSAGE_FMT(dmb, "len: %d", length);
    for (int i = offset; i < length; i++)
    {
        BGB_MESSAGE_FMT(dmb, "%d", text[i]);
        if (text[i] == 0x5C) // backslash is used start a new line
        {
            if (cur_y == 1)
            {
                cur_y++;
                cur_x = 1;
            }
            else
            {
                return_position = i + 1;
                break; // return index of next charcter so the next page can begin from there
            }
        }
        else
        {
            adjusted = adjust_char(text[i]);

            set_win_tiles(cur_x, cur_y, 1, 1, &adjusted);
            wait_vbl_done();
            cur_x++;
        }
    }

    return return_position;
}

unsigned char adjust_char(unsigned c)
{
    // 32 {space} - 0x00
    // 33 !       - 0x01
    // 63 ?       - 0x02
    // 39 '       - 0x03
    // 32 {space} - 0x00
    // 65 A       - 0x0E
    // 66 B       - 0x0F
    // 67 C       - 0x10
    // 32 {space} - 0x00
    // 97 a       - 0x28
    // 98 b       - 0x29
    // 99 c       - 0x2A

    if (c == 32)
        return 0x00;
    else if (c == 33)
        return 0x01;
    else if (c == 63)
        return 0x02;
    else if (c == 39)
        return 0x03;
    else if (c == 44)
        return 0x04;
    else if (c == 46)
        return 0x05;
    else if (c >= 48 && c < 65)
        return c - 42;
    else if (c >= 65 && c < 97)
        return c - 49;
    else if (c >= 97)
        return c - 55;
    else
        return c;
}