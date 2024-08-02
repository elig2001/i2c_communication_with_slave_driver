#include "led_indicator.h"

#define LED_FRAME 3
#define LED_SIZE 10

#define DISTANCE_FROM_LED 1.8

extern "C"
{
    void draw_led_indicator(uint32_t x, uint32_t y, char *bottom_text, uint32_t color, char *top_text, uint16_t text_size, uint16_t radius)
    {

        g_tft.fillCircle(x, y, radius + LED_FRAME, TFT_DARKGREY);
        g_tft.fillCircle(x, y, radius + 1, TFT_WHITE);
        g_tft.fillCircle(x, y, radius, color);

        g_tft.setTextSize(text_size);
        g_tft.setTextDatum(MC_DATUM);

        g_tft.drawString(bottom_text, x, y + (radius + LED_FRAME) * DISTANCE_FROM_LED);
        g_tft.drawString(top_text, x, y - (radius + LED_FRAME) * DISTANCE_FROM_LED);
    }
}
