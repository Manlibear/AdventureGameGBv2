#ifndef _MAP_DATA_H
#define _MAP_DATA_H

#include <gb/gb.h>

#define TRAVEL_TILES_COUNT 8
#define INTERACTABLE_COUNT 8
#define MAPS_COUNT 16
#define map_dataBank 2

typedef struct TravelTile
{
    UINT16 sourceX;
    UINT16 sourceY;
    unsigned char targetLayer;
    UINT16 targetX;
    UINT16 targetY;
} TravelTile;

typedef struct Interactable{
    UINT16 x;
    UINT16 y;
    unsigned char* text;
} Interactable;

typedef struct MapData
{
    const struct TravelTile travel_tiles[TRAVEL_TILES_COUNT];
    const struct Interactable interactables[INTERACTABLE_COUNT];
} MapData;

typedef struct LayerData
{
    const struct MapData maps[MAPS_COUNT];
} LayerData;

extern const struct LayerData layers_data[3];

#endif