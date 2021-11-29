#include "pendulo.h"
#include "ILI9341_STM32_Driver.h"
#include "hagl.h"
#include "arm_math.h"
#include "font5x7.h"
#include <math.h>
#include <stdlib.h>
#include "ILI9341_GFX.h"
#include <stdio.h>

Pendulo::Pendulo(TYPE x0, TYPE y0, TYPE l, TYPE mass) : x0(x0), y0(y0), l(l), mass(mass)
{
    this->a = PI / 2.0;

    this->x1 = _sin(this->a) * l;
    this->y1 = _cos(this->a) * l;
    this->color = rand() % 0xffff;
};

void Pendulo::draw()
{
    hagl_draw_circle(this->x0, this->y0, 5, color); // fixed point
    hagl_draw_line(this->x0, this->y0, this->x0 + this->old_x1, this->y0 + this->old_y1, 0); //erase the previous line
    hagl_draw_line(this->x0, this->y0, this->x0 + this->x1, this->y0 + this->y1, color); //draw the new line
    hagl_draw_circle(this->x0 + this->old_x1, this->y0 + this->old_y1, this->mass, 0); // erase the previous mass
    hagl_draw_circle(this->x0 + this->x1, this->y0 + this->y1, this->mass, color); //draw the new mass
}

void Pendulo::updatePosition()
{
    this->a += 0.1;
    this->old_x1 = this->x1;
    this->old_y1 = this->y1;
    this->x1 = _sin(this->a) * l;
    this->y1 = _cos(this->a) * l;
}