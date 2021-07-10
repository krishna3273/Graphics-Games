#include "main.h"

#ifndef EXPLOSION_H
#define EXPLOSION_H


class Explosion {
public:
    Explosion() {}
    Explosion(float x, float y, float z,float radius,color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float count;
    float radius;
    color_t color;
private:
    VAO *object;
};

#endif
