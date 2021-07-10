#include "main.h"

#ifndef BAR_H
#define BAR_H


class Bar {
public:
    Bar() {};
    Bar(float x, float y,float z, color_t color,color_t color1,color_t color2,color_t color3);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float reading);
    void tick1(float reading);
    float reading;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif
