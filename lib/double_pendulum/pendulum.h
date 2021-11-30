#ifndef PENDULUM_HPP
#define PENDULUM_HPP
#include "arm_math.h"
#include "hagl.h"

#define TYPE float32_t
#define TYPE2 float32_t
#define _sin arm_sin_f32
#define _cos arm_cos_f32

#define g 1.0

class Pendulum
{
private:
    Pendulum *node;
    TYPE x0, y0, old_x0, old_y0;
    TYPE x1, y1, old_x1, old_y1;
    TYPE mass, l;
    TYPE2 angle, angular_velocity, angular_acceleration;
    color_t color;
    void erasePreviousPendulum();

public:
    Pendulum(TYPE x0, TYPE y0, TYPE l, TYPE mass);
    Pendulum(Pendulum *p, TYPE l, TYPE mass);
    void updatePosition();
    TYPE updateAngularAcceleration(Pendulum *p);
    TYPE updateAngularAcceleration();
    void updateAngle();
    void draw();
};

#endif