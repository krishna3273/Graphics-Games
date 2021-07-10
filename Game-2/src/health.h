#include "main.h"

#ifndef HEALTH_H
#define HEALTH_H


class Health {
public:
    Health() {}
    Health(float x, float y, float z,float rx,float ry,float rz,color_t color);
    glm::vec3 position;
    float rotationx;
    float rotationy;
    float rotationz;
    int render;
    float count;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
private:
    VAO *object;
    VAO *object1;
};

#endif
