#include "../include/map_area.h"

#include "../res/maps/route_9.h"
#include "../res/maps/route_25.h"
#include "../res/maps/pallet_town.h"
#include "../res/maps/viridian_city.h"
#include "../res/maps/route_5.h"
#include "../res/maps/cerulean_city.h"
#include "../res/maps/route_24.h"
#include "../res/maps/route_1.h"
#include "../res/maps/pewter_city.h"
#include "../res/maps/route_4.h"
#include "../res/maps/route_22.h"
#include "../res/maps/route_3.h"
#include "../res/maps/route_2.h"

const MapArea areas[map_area_count] = {
    // route_9
{
        .xs = 524,
        .xe = 644,
        .ys = 88,
        .ye = 124,
        .layer = 0,
        .row_length = 120,
        .bank = 1,
        .map_data = route_9_map
},
	// route_25
{
        .xs = 504,
        .xe = 624,
        .ys = 0,
        .ye = 36,
        .layer = 0,
        .row_length = 120,
        .bank = 1,
        .map_data = route_25_map
},
	// pallet_town
{
        .xs = 104,
        .xe = 144,
        .ys = 468,
        .ye = 504,
        .layer = 0,
        .row_length = 40,
        .bank = 3,
        .map_data = pallet_town_map
},
	// viridian_city
{
        .xs = 84,
        .xe = 164,
        .ys = 324,
        .ye = 396,
        .layer = 0,
        .row_length = 80,
        .bank = 3,
        .map_data = viridian_city_map
},
	// route_5
{
        .xs = 464,
        .xe = 504,
        .ys = 144,
        .ye = 216,
        .layer = 0,
        .row_length = 40,
        .bank = 1,
        .map_data = route_5_map
},
	// cerulean_city
{
        .xs = 444,
        .xe = 524,
        .ys = 72,
        .ye = 144,
        .layer = 0,
        .row_length = 80,
        .bank = 1,
        .map_data = cerulean_city_map
},
	// route_24
{
        .xs = 464,
        .xe = 504,
        .ys = 0,
        .ye = 72,
        .layer = 0,
        .row_length = 40,
        .bank = 1,
        .map_data = route_24_map
},
	// route_1
{
        .xs = 110,
        .xe = 142,
        .ys = 396,
        .ye = 468,
        .layer = 0,
        .row_length = 32,
        .bank = 3,
        .map_data = route_1_map
},
	// pewter_city
{
        .xs = 84,
        .xe = 164,
        .ys = 108,
        .ye = 180,
        .layer = 0,
        .row_length = 80,
        .bank = 1,
        .map_data = pewter_city_map
},
	// route_4
{
        .xs = 264,
        .xe = 444,
        .ys = 88,
        .ye = 124,
        .layer = 0,
        .row_length = 180,
        .bank = 1,
        .map_data = route_4_map
},
	// route_22
{
        .xs = 0,
        .xe = 84,
        .ys = 340,
        .ye = 380,
        .layer = 0,
        .row_length = 84,
        .bank = 1,
        .map_data = route_22_map
},
	// route_3
{
        .xs = 164,
        .xe = 304,
        .ys = 124,
        .ye = 160,
        .layer = 0,
        .row_length = 140,
        .bank = 1,
        .map_data = route_3_map
},
	// route_2
{
        .xs = 104,
        .xe = 144,
        .ys = 180,
        .ye = 324,
        .layer = 0,
        .row_length = 40,
        .bank = 3,
        .map_data = route_2_map
},
	
};