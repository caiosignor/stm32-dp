#include "pendulum.h"
#include "ILI9341_STM32_Driver.h"
#include "hagl.h"
#include "arm_math.h"
#include "font5x7.h"
#include <stdlib.h>
#include "ILI9341_GFX.h"
#include <stdio.h>

Pendulum::Pendulum(Pendulum *p, TYPE l, TYPE mass) : node(p), mass(mass), l(l)
{
    this->angle = PI / 2;
    x0 = p->x1;
    y0 = p->y1;
    //a = p->a;
    color = p->color + 255;
}

Pendulum::Pendulum(TYPE x0, TYPE y0, TYPE l, TYPE mass) : x0(x0), y0(y0), l(l), mass(mass)
{
    node = nullptr;
    this->angle = PI / 2.0;
    this->x1 = _sin(this->angle) * l;
    this->y1 = _cos(this->angle) * l;
    this->color = rand() % 0xffff;
};

void Pendulum::draw()
{
    if (this->node == nullptr)
        hagl_draw_circle(this->x0, this->y0, 5, color); // fixed point

    this->erasePreviousPendulum();
    hagl_draw_line(this->x0, this->y0, this->x0 + this->x1, this->y0 + this->y1, color); //draw the new line
    hagl_draw_circle(this->x0 + this->x1, this->y0 + this->y1, this->mass, color);       //draw the new mass
}

void Pendulum::erasePreviousPendulum()
{
    TYPE _x0, _y0;
    _x0 = this->node == nullptr ? this->x0 : this->old_x0;
    _y0 = this->node == nullptr ? this->y0 : this->old_y0;
    hagl_draw_line(_x0, _y0, _x0 + this->old_x1, _y0 + this->old_y1, 0);     //erase the previous line
    hagl_draw_circle(_x0 + this->old_x1, _y0 + this->old_y1, this->mass, 0); // erase the previous mass
}

void Pendulum::updateAngle()
{
    this->angle += this->angular_velocity;
    this->angular_velocity += this->angular_acceleration;
}

void Pendulum::updatePosition()
{
    if (this->node != nullptr)
    {
        this->old_x0 = this->x0;
        this->old_y0 = this->y0;
        this->x0 = this->node->x0 + this->node->x1 + this->node->mass;
        this->y0 = this->node->y0 + this->node->y1;
    }

    this->updateAngle();

    this->old_x1 = this->x1;
    this->old_y1 = this->y1;
    this->x1 = _sin(this->angle) * l;
    this->y1 = _cos(this->angle) * l;
}

TYPE Pendulum::updateAngularAcceleration(Pendulum *p)
{
    this->angular_acceleration =
        (-g * (2 * this->mass + p->mass) * _sin(this->angle) - p->mass * g * _sin(this->angle - 2 * p->angle) - 2 * _sin(this->angle - p->angle) * p->mass * (p->angular_velocity * p->angular_velocity * p->l + this->angular_velocity * this->angular_velocity * this->l * _cos(this->angle - p->angle))) / (this->l * (2 * this->mass + p->mass - p->mass * _cos(2 * this->angle - 2 * p->angle)));

    return this->angular_acceleration;
}

TYPE Pendulum::updateAngularAcceleration()
{
    this->angular_acceleration =
        ((2 * _sin(node->angle - this->angle)) * (node->angular_velocity * node->angular_velocity * node->l * (node->mass + this->mass) + g * (node->mass + this->mass) * _cos(node->angle) + this->angular_velocity * this->angular_velocity * this->l * this->mass * _cos(node->angle - this->angle))) / (this->l * (2 * node->mass + this->mass - this->mass * _cos(2 * node->angle - 2 * this->angle)));

    return this->angular_acceleration;
}