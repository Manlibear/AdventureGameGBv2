#ifndef _DEBUG_H
#define _DEBUG_H
#define _DEBUG_TOOLS_ENABLED

#ifdef _DEBUG_TOOLS_ENABLED

#include <gb/bgb_emu.h>
#include "player_controller.h"
#include <stdio.h>

void BGB_print_xy();

extern unsigned char dmb[200];

#endif


#endif