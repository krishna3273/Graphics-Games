#include "main.h"

#ifndef BOOM_H
#define BOOM_H


class Boom {
public:
    Boom() {}
    Boom(float x, float y, color_t color,float v1,float v2);
    float vx;
    float vy;
    int dir;
    float rotation;
    float width;
    float height;
    glm ::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif 
