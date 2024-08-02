#include "ring_meter.h"

int xpos = 0, ypos = 5, gap = 4, radius = 52;

//  xpos = 480/2 - 160, ypos = 0, gap = 15, radius = 170;
//     reading +=(ramp);
//     if (reading>98) ramp = -1;
//     if (reading<0) ramp = 1;
//     // Comment out above meters, then uncomment the next line to show large meter
//     ringMeter(reading,0,100, xpos,ypos,radius," Watts",GREEN2RED); // Draw analogue meter
//     if (reading<0) delay(1000);

extern "C"
{
    static unsigned int rainbow(byte value);
    static float sineWave(int phase);
}


extern "C"
{
    int ring_meter(int value, int vmin, int vmax, int x, int y, int r, const char *units, byte scheme)
    {
        // Minimum value of r is about 52 before value text intrudes on ring
        // drawing the text first is an option

        x += r;
        y += r; // Calculate coords of centre of ring

        int w = r / 3; // Width of outer ring is 1/4 of radius

        int angle = 150; // Half the sweep angle of meter (300 degrees)

        int v = map(value, vmin, vmax, -angle, angle); // Map the value to an angle v

        byte seg = 3; // Segments are 3 degrees wide = 100 segments for 300 degrees
        byte inc = 6; // Draw segments every 3 degrees, increase to 6 for segmented ring

        // Variable to save "value" text colour from scheme and set default
        int colour = TFT_BLUE;

        // Convert value to a string
        char buf[10];
        byte len = 3;
        if (value > 999)
            len = 5;
        dtostrf(value, len, 0, buf);
        buf[len] = ' ';
        buf[len + 1] = 0; // Add blanking space and terminator, helps to centre text too!
        // Set the text colour to default
        g_tft.setTextSize(3);
        g_tft.setTextPadding(0);


        //   if (value<vmin || value>vmax) {
        //     drawAlert(x,y+90,50,1);
        //   }
        //   else {
        //     drawAlert(x,y+90,50,0);
        //   }

        g_tft.setTextColor(TFT_WHITE, TFT_BLACK);
        // Uncomment next line to set the text colour to the last segment value!
        g_tft.setTextColor(TFT_GREEN, TFT_BLACK);
        g_tft.setTextDatum(MC_DATUM);
        // Print value, if the meter is large then use big font 8, othewise use 4
        if (r > 84)
        {
            // g_tft.setTextPadding(55 * 3);   // Allow for 3 digits each 55 pixels wide
            g_tft.drawString(buf, x, y); // Value in middle
        }
        else
        {
            // g_tft.setTextPadding(3 * 14);   // Allow for 3 digits each 14 pixels wide
            g_tft.drawString(buf, x + 10, y); // Value in middle
        }
        g_tft.setTextSize(2);
        g_tft.setTextPadding(0);
        // Print units, if the meter is large then use big font 4, othewise use 2
        g_tft.setTextColor(TFT_WHITE, TFT_BLACK);
        // if (r > 84)
            g_tft.drawString(units, x+3, y + 50); // Units display
        // else
        //     g_tft.drawString(units, x, y + 15, 0); // Units display

        // Calculate and return right hand side x coordinate

        // Draw colour blocks every inc degrees
        for (int i = -angle + inc / 2; i < angle - inc / 2; i += inc)
        {
            // Calculate pair of coordinates for segment start
            float sx = cos((i - 90) * 0.0174532925);
            float sy = sin((i - 90) * 0.0174532925);
            uint16_t x0 = sx * (r - w) + x;
            uint16_t y0 = sy * (r - w) + y;
            uint16_t x1 = sx * r + x;
            uint16_t y1 = sy * r + y;

            // Calculate pair of coordinates for segment end
            float sx2 = cos((i + seg - 90) * 0.0174532925);
            float sy2 = sin((i + seg - 90) * 0.0174532925);
            int x2 = sx2 * (r - w) + x;
            int y2 = sy2 * (r - w) + y;
            int x3 = sx2 * r + x;
            int y3 = sy2 * r + y;

            if (i < v)
            { // Fill in coloured segments with 2 triangles
                switch (scheme)
                {
                case 0:
                    colour = TFT_RED;
                    break; // Fixed colour
                case 1:
                    colour = TFT_GREEN;
                    break; // Fixed colour
                case 2:
                    colour = TFT_BLUE;
                    break; // Fixed colour
                case 3:
                    colour = rainbow(map(i, -angle, angle, 0, 127));
                    break; // Full spectrum blue to red
                case 4:
                    colour = rainbow(map(i, -angle, angle, 70, 127));
                    break; // Green to red (high temperature etc.)
                case 5:
                    colour = rainbow(map(i, -angle, angle, 127, 63));
                    break; // Red to green (low battery etc.)
                default:
                    colour = TFT_BLUE;
                    break; // Fixed colour
                }
                g_tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
                g_tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);
                // text_colour = colour; // Save the last colour drawn
            }
            else // Fill in blank segments
            {
                g_tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_DARKGREY);
                g_tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_DARKGREY);
            }
        }
        
        return x + r;
    }

    // #########################################################################
    // Return a 16-bit rainbow colour
    // #########################################################################

    static unsigned int rainbow(byte value)
    {
        // Value is expected to be in range 0-127
        // The value is converted to a spectrum colour from 0 = blue through to 127 = red

        byte red = 0;   // Red is the top 5 bits of a 16-bit colour value
        byte green = 0; // Green is the middle 6 bits
        byte blue = 0;  // Blue is the bottom 5 bits

        byte quadrant = value / 32;

        if (quadrant == 0)
        {
            blue = 31;
            green = 2 * (value % 32);
            red = 0;
        }
        if (quadrant == 1)
        {
            blue = 31 - (value % 32);
            green = 63;
            red = 0;
        }
        if (quadrant == 2)
        {
            blue = 0;
            green = 63;
            red = value % 32;
        }
        if (quadrant == 3)
        {
            blue = 0;
            green = 63 - 2 * (value % 32);
            red = 31;
        }
        return (red << 11) + (green << 5) + blue;
    }

    // #########################################################################
    // Return a value in range -1 to +1 for a given phase angle in degrees
    // #########################################################################
    static float sineWave(int phase)
    {
        return sin(phase * 0.0174532925);
    }
}
