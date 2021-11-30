#include "loop.h"
#include <stdlib.h>
#include <stdint.h>
#include "main.h"
#include "ILI9341_STM32_Driver.h"
#include "hagl.h"
#include "pendulum.h"
#include "font5x8.h"
#include "ILI9341_GFX.h"

Pendulum p1(100, 120, 70, 15), p2(&p1, 70, 15);

void setup()
{
    ILI9341_Init();
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
    hagl_init();
}

void loop()
{
    p1.updateAngularAcceleration(&p2);
    p2.updateAngularAcceleration();
    p1.updatePosition();
    p2.updatePosition();
    p1.draw();
    p2.draw();
    p1.updateAngle();
    p2.updateAngle();
    hagl_flush();
    HAL_Delay(1);
}
