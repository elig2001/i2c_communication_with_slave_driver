#pragma once

#include <TFT_eSPI.h> // Master copy here: https://github.com/Bodmer/TFT_eSPI

extern TFT_eSPI g_tft;

extern "C"
{
    void draw_info_panel();
    void draw_gas_panel();
    void draw_main_panel(int value, int vmin, int vmax, float Ofset_L, float Ofset_H, const char *units  );
    void draw_control_panel();
    void draw_screen();
}