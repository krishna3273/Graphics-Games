#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {};
    Arrow(float x, float y, float z,color_t color,int type);
    glm::vec3 position;
    // float count;
    float v;
    float scale;
    float rotationy;
    float rotationx;
    float rotationz;
    int type;
    void draw(glm::mat4 VP,float x1,float y1,float z1);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object1;
    VAO *object2;
};

#endif
