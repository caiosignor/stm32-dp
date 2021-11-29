#include "pendulo.h"
#include "ILI9341_STM32_Driver.h"
#include "hagl.h"
#include "arm_math.h"
#include "font5x7.h"
#include <math.h>
#include <stdlib.h>
#include "ILI9341_GFX.h"
#include <stdio.h>

Pendulo::Pendulo(TYPE x0, TYPE y0, TYPE l) : x0(x0), y0(y0), l(l)
{
    this->a = PI / 2.0;

    this->x1 = _sin(this->a) * l;
    this->y1 = _cos(this->a) * l;
    this->color = rand() % 0xffff;
};

void Pendulo::draw()
{
    hagl_draw_circle(this->x0, this->y0, 5, color);
    hagl_draw_line(this->x0, this->y0, this->x0 + this->old_x1, this->y0 + this->old_y1, 0);
    hagl_draw_line(this->x0, this->y0, this->x0 + this->x1, this->y0 + this->y1, color);
    HAL_Delay(10);
}

void Pendulo::updatePosition()
{
    this->a += 0.1;
    this->old_x1 = this->x1;
    this->old_y1 = this->y1;
    this->x1 = _sin(this->a) * l;
    this->y1 = _cos(this->a) * l;

    //char str_x1[32], str_y1[32];
    //sprintf(str_x1, "x1 = %.3f ", this->x1);
    //sprintf(str_y1, "y1 = %.3f ", this->y1);
//
    //ILI9341_Draw_Text(str_x1, 100, 10, BLACK, 2, WHITE);
    //ILI9341_Draw_Text(str_y1, 100, 50, BLACK, 2, WHITE);
}