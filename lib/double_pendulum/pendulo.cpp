#include "pendulo.h"
#include "ILI9341_STM32_Driver.h"
#include "hagl.h"
#include "arm_math.h"
#include "font5x7.h"
#include <math.h>
#include <stdlib.h>
#include "ILI9341_GFX.h"
#include <stdio.h>

Pendulo::Pendulo(Pendulo *p, TYPE l, TYPE mass) : node(p), mass(mass), l(l)
{
    this->a = PI / 2;
    x0 = p->x1;
    y0 = p->y1;
    //a = p->a;
    color = p->color + 255;
}

Pendulo::Pendulo(TYPE x0, TYPE y0, TYPE l, TYPE mass) : x0(x0), y0(y0), l(l), mass(mass)
{
    node = nullptr;
    this->a = PI / 2.0;
    this->x1 = _sin(this->a) * l;
    this->y1 = _cos(this->a) * l;
    this->color = rand() % 0xffff;
};

void Pendulo::draw()
{
    if (this->node == nullptr)
        hagl_draw_circle(this->x0, this->y0, 5, color); // fixed point

    this->erasePreviousPendulum();
    hagl_draw_line(this->x0, this->y0, this->x0 + this->x1, this->y0 + this->y1, color); //draw the new line
    hagl_draw_circle(this->x0 + this->x1, this->y0 + this->y1, this->mass, color);       //draw the new mass
}

void Pendulo::erasePreviousPendulum()
{
    TYPE _x0, _y0;
    _x0 = this->node == nullptr ? this->x0 : this->old_x0;
    _y0 = this->node == nullptr ? this->y0 : this->old_y0;
    hagl_draw_line(_x0, _y0, _x0 + this->old_x1, _y0 + this->old_y1, 0);     //erase the previous line
    hagl_draw_circle(_x0 + this->old_x1, _y0 + this->old_y1, this->mass, 0); // erase the previous mass
}

void Pendulo::updatePosition()
{
    if (this->node != nullptr)
    {
        this->old_x0 = this->x0;
        this->old_y0 = this->y0;
        this->x0 = this->node->x0 + this->node->x1 + this->node->mass;
        this->y0 = this->node->y0 + this->node->y1;
    }
    else
    {
        this->a += 0.1;
    }
    this->old_x1 = this->x1;
    this->old_y1 = this->y1;
    this->x1 = _sin(this->a) * l;
    this->y1 = _cos(this->a) * l;
}