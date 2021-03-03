#include "overworld_palette.h"

unsigned char overworld_tile_pal(unsigned char tn)
{
	switch(tn){
		case 0x68:
			return 1;

		case 0x69:
		case 0x6A:
		case 0x6C:
		case 0x6D:
		case 0x6E:
		case 0x6F:
			return 2;
	}	
	return 0;
}