#include "../include/screen.h"
#include "../include/debug.h"

#define FADE_STEPS 4


UWORD spritePalette[] = {
	RGB_WHITE, RGB_LIGHTGRAY, RGB_DARKGRAY, RGB_BLACK
};

UWORD bkgPalette[] = {
    RGB_WHITE, RGB_LIGHTGRAY, RGB_DARKGRAY, RGB_BLACK,
    RGB(15, 31, 15), RGB(9, 31, 9), RGB_DARKGREEN, RGB_BLACK,
    RGB(27, 27, 21), RGB(20, 20, 0), RGB_BROWN, RGB_BLACK
};

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
        // BGP_REG = (0xFFE4 >> (i << 1));
        // OBP0_REG = (0xFFE4 >> (i << 1));
        
        set_bkg_palette_entry(0, 1-i, RGB_LIGHTGRAY);
        set_bkg_palette_entry(0, 2-i, RGB_DARKGRAY);
        set_bkg_palette_entry(0, 3-i, RGB_BLACK);

        set_sprite_palette_entry(0, 1-i, RGB_LIGHTGRAY);
        set_sprite_palette_entry(0, 2-i, RGB_DARKGRAY);
        set_sprite_palette_entry(0, 3-i, RGB_BLACK);

        for (int j = 0; j < fade_delay; j++)
            wait_vbl_done();
    }
}

void fade_in()
{
    for (int i = FADE_STEPS; i >= 0; --i)
    {
        // BGP_REG = (0xFFE4 >> (i << 1));
        // OBP0_REG = (0xFFE0 >> (i << 1));
        // set_sprite_palette(i - 1, 4, fade_palettes);
        // set_bkg_palette(i - 1, 4, fade_palettes);
        
        switch (i)
        {
            case 4:
                set_bkg_palette_entry(0, 0, spritePalette[2]);
                set_sprite_palette_entry(0, 0, spritePalette[2]);        
                break;
                
            case 3:
                set_bkg_palette_entry(0, 0, spritePalette[1]);
                set_bkg_palette_entry(0, 1, spritePalette[2]);
                
                set_sprite_palette_entry(0, 0, spritePalette[1]);
                set_sprite_palette_entry(0, 1, spritePalette[2]);
                break;
                
            case 2:
                set_bkg_palette_entry(0, 0, spritePalette[0]);
                set_bkg_palette_entry(0, 1, spritePalette[1]);
                set_bkg_palette_entry(0, 2, spritePalette[2]);
                
                set_sprite_palette_entry(0, 0, spritePalette[0]);
                set_sprite_palette_entry(0, 1, spritePalette[1]);
                set_sprite_palette_entry(0, 2, spritePalette[2]);
                break;
            
            default:
                break;
        }

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

    VBK_REG = 1;
    SWITCH_ROM_MBC1(ui_tilesBank);
    set_win_data(0x5F, ui_tiles_count, ui_tiles);

    SWITCH_ROM_MBC1(fontBank);
    set_win_data(0, font_length, font);
    fill_win_rect(0, 0, 20, 4, 0x08);
    
    VBK_REG = 0;

    
    SWITCH_ROM_MBC1(ui_mapBank);
    set_win_tiles(0, 0, 20, 4, ui_map);

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

    for (int i = offset; i < length; i++)
    {
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