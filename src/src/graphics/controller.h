#pragma once

#include <TFT_eSPI.h> // Master copy here: https://github.com/Bodmer/TFT_eSPI

extern TFT_eSPI g_tft;

extern "C"
{
    void draw_controller(uint32_t x, uint32_t y, uint32_t color);
}