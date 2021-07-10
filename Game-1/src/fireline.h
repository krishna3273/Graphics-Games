#include "main.h"

#ifndef FIRELINE_H
#define FIRELINE_H


class Fireline {
public:
    Fireline() {}
    Fireline(float x, float y, color_t color,float angle,float vx,float vy);
    glm::vec3 position;
    float vx;
    float vy;
    float x_shi;
    float y_shi;
    int active;
    color_t color;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif 