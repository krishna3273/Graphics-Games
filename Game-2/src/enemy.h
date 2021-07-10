#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {};
    Enemy(float x, float y, float z,color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float rx;
    float ry;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif
