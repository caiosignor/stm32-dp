#include "loop.h"

#include "main.h"
#include "ILI9341_STM32_Driver.h"
#include "hagl.h"

void setup()
{
    ILI9341_Init();
    //ILI9341_Fill_Screen(BLUE);
    hagl_init();
}

void loop()
{
    for (uint32_t i = 1; i < 100000; i++)
    {
        int16_t x0 = i % DISPLAY_WIDTH;
        int16_t y0 = i % DISPLAY_HEIGHT;
        color_t color = i % 0xffff;

        hagl_put_pixel(x0, y0, color);
    }
    hagl_flush();
}
