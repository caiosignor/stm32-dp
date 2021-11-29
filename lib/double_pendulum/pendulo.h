#ifndef PENDULO_HPP
#define PENDULO_HPP
#include "arm_math.h"
#include "hagl.h"

#define TYPE float32_t
#define TYPE2 float32_t
#define _sin arm_sin_f32
#define _cos arm_cos_f32

class Pendulo
{
private:
    TYPE x0, y0, old_x0, old_y0;
    TYPE x1, y1, old_x1, old_y1;
    TYPE l;
    TYPE2 a;
    color_t color;

public:
    Pendulo(TYPE x0, TYPE y0, TYPE l);
    void updatePosition();
    void draw();
};

#endif