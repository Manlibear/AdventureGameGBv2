#include "../include/map_area.h"

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

#include "../res/pals/overworld_palette.h"


const MapArea areas[map_area_count] = {
    // pallet_town
{
        .xs = 104,
        .xe = 143,
        .ys = 468,
        .ye = 503,
        .layer = 0,
        .row_length = 40,
        .bank = 7,
        .area_index = 0,
        .adjacents = {12},
        .map_data = pallet_town_map,
        .get_tile_palette = &overworld_tile_pal
},
	// route_3
{
        .xs = 164,
        .xe = 303,
        .ys = 124,
        .ye = 159,
        .layer = 0,
        .row_length = 140,
        .bank = 5,
        .area_index = 1,
        .map_data = route_3_map
},
	// route_5
{
        .xs = 464,
        .xe = 503,
        .ys = 144,
        .ye = 215,
        .layer = 0,
        .row_length = 40,
        .bank = 1,
        .area_index = 2,
        .map_data = route_5_map
},
	// route_22
{
        .xs = 0,
        .xe = 83,
        .ys = 340,
        .ye = 379,
        .layer = 0,
        .row_length = 84,
        .bank = 5,
        .area_index = 3,
        .map_data = route_22_map
},
	// route_9
{
        .xs = 524,
        .xe = 643,
        .ys = 88,
        .ye = 123,
        .layer = 0,
        .row_length = 120,
        .bank = 1,
        .area_index = 4,
        .map_data = route_9_map
},
	// pewter_city
{
        .xs = 84,
        .xe = 163,
        .ys = 108,
        .ye = 179,
        .layer = 0,
        .row_length = 80,
        .bank = 5,
        .area_index = 5,
        .map_data = pewter_city_map
},
	// route_25
{
        .xs = 504,
        .xe = 623,
        .ys = 0,
        .ye = 35,
        .layer = 0,
        .row_length = 120,
        .bank = 1,
        .area_index = 6,
        .map_data = route_25_map
},
	// route_24
{
        .xs = 464,
        .xe = 503,
        .ys = 0,
        .ye = 71,
        .layer = 0,
        .row_length = 40,
        .bank = 4,
        .area_index = 7,
        .map_data = route_24_map
},
	// route_2
{
        .xs = 104,
        .xe = 143,
        .ys = 180,
        .ye = 323,
        .layer = 0,
        .row_length = 40,
        .bank = 6,
        .area_index = 8,
        .map_data = route_2_map
},
	// viridian_city
{
        .xs = 84,
        .xe = 163,
        .ys = 324,
        .ye = 395,
        .layer = 0,
        .row_length = 80,
        .bank = 6,
        .area_index = 9,
        .map_data = viridian_city_map
},
	// cerulean_city
{
        .xs = 444,
        .xe = 523,
        .ys = 72,
        .ye = 143,
        .layer = 0,
        .row_length = 80,
        .bank = 4,
        .area_index = 10,
        .map_data = cerulean_city_map
},
	// route_4
{
        .xs = 264,
        .xe = 443,
        .ys = 88,
        .ye = 123,
        .layer = 0,
        .row_length = 180,
        .bank = 4,
        .area_index = 11,
        .map_data = route_4_map
},
	// route_1
{
        .xs = 110,
        .xe = 141,
        .ys = 396,
        .ye = 467,
        .layer = 0,
        .row_length = 32,
        .bank = 6,
        .area_index = 12,
        .adjacents = {0, 10},
        .map_data = route_1_map,
        .get_tile_palette = &overworld_tile_pal
},
	// oaks_lab
{
        .xs = 67,
        .xe = 88,
        .ys = 475,
        .ye = 500,
        .layer = 1,
        .row_length = 22,
        .bank = 10,
        .area_index = 0,
        .map_data = oaks_lab_map,
        .get_tile_palette = &overworld_tile_pal
},
	// players_house_1f
{
        .xs = 41,
        .xe = 58,
        .ys = 480,
        .ye = 497,
        .layer = 1,
        .row_length = 18,
        .bank = 9,
        .area_index = 1,
        .map_data = players_house_1f_map
},
	// rivals_house
{
        .xs = 67,
        .xe = 84,
        .ys = 449,
        .ye = 466,
        .layer = 1,
        .row_length = 18,
        .bank = 10,
        .area_index = 2,
        .map_data = rivals_house_map
},
	// players_house_gf
{
        .xs = 41,
        .xe = 58,
        .ys = 449,
        .ye = 466,
        .layer = 1,
        .row_length = 18,
        .bank = 10,
        .area_index = 3,
        .map_data = players_house_gf_map
},
	
};