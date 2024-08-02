#pragma once

#include <TFT_eSPI.h> // Master copy here: https://github.com/Bodmer/TFT_eSPI

extern TFT_eSPI g_tft;

extern "C"
{
    void draw_led_indicator(uint32_t x, uint32_t y, char *name, uint32_t color, char *value, uint16_t text_size, uint16_t radius);
}
