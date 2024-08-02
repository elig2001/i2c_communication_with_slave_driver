#include "controller.h"
#include "led_indicator.h"

#define CONTROLLER_RADIUS 30
#define CONTROLLER_BORDER_WIDTH 10
#define CONTROLLER_FRAME 3

#define Y_DISTANCE_FROM_BUTTON CONTROLLER_RADIUS * 0.8

enum aligment_amount_e
{
    ALIGNMENT_AMOUNT_PAPR = 9,
    ALIGNMENT_AMOUNT_CC = 7,
    ALIGNMENT_AMOUNT_OFF = 7
};

extern "C"
{
    static void draw_rectangle_around_text(int16_t text_size, int32_t x, int32_t y, uint32_t color, aligment_amount_e alignment_amount);
}

extern "C"
{
    void draw_controller(uint32_t x, uint32_t y, uint32_t color)
    {
        int16_t text_size = 0;

        g_tft.fillCircle(x, y, CONTROLLER_RADIUS + CONTROLLER_FRAME, TFT_DARKGREY);

        g_tft.fillCircle(x, y, CONTROLLER_RADIUS, color);

        g_tft.fillCircle(x, y, CONTROLLER_RADIUS - CONTROLLER_BORDER_WIDTH + CONTROLLER_FRAME, TFT_DARKGREY);
        g_tft.fillCircle(x, y, CONTROLLER_RADIUS - CONTROLLER_BORDER_WIDTH, TFT_BLACK);

        g_tft.setTextSize(2);
        text_size = g_tft.drawString("C.C", x - (CONTROLLER_RADIUS * 2.5), y - (Y_DISTANCE_FROM_BUTTON));

        text_size = g_tft.drawString("PAPR", x + (CONTROLLER_RADIUS * 2.5), y - (Y_DISTANCE_FROM_BUTTON));
        draw_rectangle_around_text(text_size, x + (CONTROLLER_RADIUS * 2.5), y - (Y_DISTANCE_FROM_BUTTON), color, ALIGNMENT_AMOUNT_PAPR);

        text_size = g_tft.drawString("OFF", x + (CONTROLLER_RADIUS * 2.5), y + Y_DISTANCE_FROM_BUTTON);

        draw_led_indicator(x - (CONTROLLER_RADIUS * 2.5), y + (Y_DISTANCE_FROM_BUTTON), "", color, "LIT", 1, 8);

        g_tft.setTextSize(1);
        g_tft.drawString("Mode", x + 2, y);
    }

    /*
    text_size[in]: should be retrieved from drawString function
    x[in]: the x of drawn string in MC_DATUM state
    y[in]: the y of the draw string in MC_DATUM state
    color[in]: the color you would like
    */
    static void draw_rectangle_around_text(int16_t text_size, int32_t x, int32_t y, uint32_t color, aligment_amount_e alignment_amount)
    {
        g_tft.drawRect(x - (text_size / 2) - alignment_amount, y - (CONTROLLER_RADIUS * 0.5) - 1, text_size * 1.3, 30, color);
    }
}