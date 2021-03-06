#ifndef _MAP_DATA_H
#define _MAP_DATA_H

#include <gb/gb.h>
#include "../res/maps/pallet_town_map.h"
#include "../res/maps/route_3_map.h"
#include "../res/maps/route_5_map.h"
#include "../res/maps/route_22_map.h"
#include "../res/maps/route_9_map.h"
#include "../res/maps/pewter_city_map.h"
#include "../res/maps/route_25_map.h"
#include "../res/maps/route_24_map.h"
#include "../res/maps/route_2_map.h"
#include "../res/maps/viridian_city_map.h"
#include "../res/maps/cerulean_city_map.h"
#include "../res/maps/route_4_map.h"
#include "../res/maps/route_1_map.h"
#include "../res/maps/oaks_lab_map.h"
#include "../res/maps/players_house_1f_map.h"
#include "../res/maps/rivals_house_map.h"
#include "../res/maps/players_house_gf_map.h"
#include "../res/tiles/indoors.h"
#include "../res/tiles/overworld.h"

#define TRAVEL_TILES_COUNT 4
#define INTERACTABLE_COUNT 4
#define MAPS_COUNT 15

typedef struct TravelTile
{
    const UINT16 sourceX;
    const UINT16 sourceY;
    const unsigned char targetLayer;
    const UINT16 targetX;
    const UINT16 targetY;
} TravelTile;

typedef struct Interactable{
    const UINT16 x;
    const UINT16 y;
    const unsigned char* text;
} Interactable;

typedef struct MapData
{
    const struct TravelTile (*travel_tiles)[TRAVEL_TILES_COUNT];
    const struct Interactable  (*interactables)[INTERACTABLE_COUNT];
} MapData;

typedef struct LayerData
{
    const struct MapData maps[MAPS_COUNT];
} LayerData;

extern const struct LayerData layers_data[3];

#endif