#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z,float vx,float vy,float vz,color_t color);
    glm::vec3 position;
    float vx;
    float vy;
    float vz;
    int render;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
private:
    VAO *object;
};

#endif
