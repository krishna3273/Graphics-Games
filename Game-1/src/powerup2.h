#include "main.h"

#ifndef POWERUP2_H
#define POWERUP2_H


class Powerup2 {
public:
    Powerup2() {}
    Powerup2(float x, float y, color_t color,float v1,float v2);
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
