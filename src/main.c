#include <tice.h>
#include <graphx.h>
#include <stdint.h>
#include <stdlib.h>

#include "gfx/hej_gfx.h"

void main(void) {

    gfx_Begin();
    
    gfx_SetPalette(hej_gfx_pal, sizeof_hej_gfx_pal, 0);

    gfx_FillScreen(0);
    
    gfx_Sprite(hej, 0, 0);
    gfx_Sprite_NoClip(hej, 32, 32);
    gfx_TransparentSprite(hej, 64, 64);
    gfx_TransparentSprite_NoClip(hej, 96, 96);
    gfx_ScaledSprite_NoClip(hej, 128, 128, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(hej, 128, 0, 3, 3);

    gfx_SetTextXY(120,20);
    gfx_SetTextFGColor(0);
    gfx_SetTextTransparentColor(255);
    gfx_PrintString("Schema");

    while(os_GetCSC() != 9);

    gfx_End();
}