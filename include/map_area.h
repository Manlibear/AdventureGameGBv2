#ifndef _MAP_AREA
#define _MAP_AREA
#define map_area_count 15

#include <gb/gb.h>

typedef struct MapArea
{
    UINT16 xs;
    UINT16 xe;
    UINT16 ys;
    UINT16 ye;
    char area_index;
    unsigned char row_length;
    unsigned char layer;
    unsigned char bank;
    unsigned char* map_data;
} MapArea;

extern const MapArea areas[map_area_count];



#endif