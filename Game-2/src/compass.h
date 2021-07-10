#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {};
    Compass(float x, float y, float z,color_t color);
    glm::vec3 position;
    // float count;
    float v;
    float scale;
    float rotationy;
    float rotationx;
    float rotationz;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif
