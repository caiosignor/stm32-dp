#include "loop.h"
#include <stdlib.h>
#include <stdint.h>
#include "main.h"
#include "ILI9341_STM32_Driver.h"
#include "hagl.h"
#include "pendulo.h"
#include "font5x8.h"
#include "ILI9341_GFX.h"

Pendulo p1(100, 120, 70, 10), p2(&p1, 50, 15);

void setup()
{
    ILI9341_Init();
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
    hagl_init();
}

void loop()
{
    p1.updatePosition();
    p1.draw();
    p2.updatePosition();
    p2.draw();
    hagl_flush();
    HAL_Delay(10);
}
