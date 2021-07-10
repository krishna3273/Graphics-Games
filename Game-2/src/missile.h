#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z,float vx,float vy,float vz,float rx,float ry,float rz,color_t color);
    glm::vec3 position;
    float vx;
    float vy;
    float vz;
    float rotationx;
    float rotationy;
    float rotationz;
    int render;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object1;
    VAO *object2;
};

#endif
