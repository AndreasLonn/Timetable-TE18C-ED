// convpng v6.8
// this file contains all the graphics sources for easy inclusion in a project
#ifndef __hej_gfx__
#define __hej_gfx__
#include <stdint.h>

#define hej_gfx_transparent_color_index 0

#define hej_width 16
#define hej_height 16
#define hej_size 258
extern uint8_t hej_data[258];
#define hej ((gfx_sprite_t*)hej_data)
#define sizeof_hej_gfx_pal 4
extern uint16_t hej_gfx_pal[2];

#endif
