#include "main.h"

#ifndef POWERUP1_H
#define POWERUP1_H


class Powerup1 {
public:
    Powerup1() {}
    Powerup1(float x, float y, color_t color,float v1,float v2);
    float vx;
    float vy;
    float radius;
    float width;
    float height;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif 
