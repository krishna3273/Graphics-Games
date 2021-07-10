#include "main.h"

#ifndef SMOKE_H
#define SMOKE_H


class Smoke {
public:
    Smoke() {}
    Smoke(float x, float y, float z,color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    int count;
private:
    VAO *object;
};

#endif
