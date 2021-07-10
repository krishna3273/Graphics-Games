#include "main.h"
#include "fireline.h"

#ifndef FIREBALL_H
#define FIREBALL_H


class Fireball {
public:
    Fireball() {}
    Fireball(float x, float y, color_t color,float v);
    Fireline f1;
    Fireline f2;
    void draw(glm::mat4 VP);
    void tick();
    float v;
    float centre;
};

#endif 