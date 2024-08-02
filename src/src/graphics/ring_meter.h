#pragma once

#include <TFT_eSPI.h> // Master copy here: https://github.com/Bodmer/TFT_eSPI

#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5

extern TFT_eSPI g_tft;

extern "C"
{
    int ring_meter(int value, int vmin, int vmax, int x, int y, int r, const char *units, byte scheme);
}
