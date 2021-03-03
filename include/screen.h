#ifndef _SCREEN_H
#define _SCREEN_H

#include <gb/gb.h>
#include <gb/cgb.h>
#include "../res/ui/ui_map.h"
#include "../res/ui/ui_tiles.h"
#include "../res/ui/font.h"

extern char window_showing;
extern int text_window_offset;
extern int text_window_length;
extern unsigned char text_window_bank;
extern unsigned char* text_window_text;
extern UWORD spritePalette[];
extern UWORD bkgPalette[];

void fade_out_black();
void fade_in();
int show_text_window(unsigned char *text, int length, unsigned char text_bank, int offset);
void hide_window();
unsigned char adjust_char(unsigned c);

#endif