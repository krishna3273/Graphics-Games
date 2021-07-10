#include<bits/stdc++.h>
#include "bomb.h"
#include "main.h"
using namespace std;

Bomb::Bomb(float x, float y,float z,float vx,float vy,float vz ,color_t color) {

    this->position = glm::vec3(x, y, z);
    this->vx=vx;
    this->vy=vy;
    this->vz=vz;
    this->render=1;
    GLfloat vertex_buffer_data[]={
        -0.125f,0.125f,0.125f,
        0.125f,0.125f,0.125f,
        0.125f,-0.125f,0.125f,
        -0.125f,0.125f,0.125f,
        0.125f,-0.125f,0.125f,
        -0.125f,-0.125f,0.125f,


        -0.125f,0.125f,-0.125f,
        0.125f,0.125f,-0.125f,
        0.125f,-0.125f,-0.125f,
        -0.125f,0.125f,-0.125f,
        0.125f,-0.125f,-0.125f,
        -0.125f,-0.125f,-0.125f,


        0.125f,0.125f,-0.125f,
        0.125f,0.125f,0.125f,
        0.125f,-0.125f,0.125f,
        0.125f,0.125f,-0.125f,
        0.125f,-0.125f,0.125f,
        0.125f,-0.125f,-0.125f,


        -0.125f,0.125f,-0.125f,
        -0.125f,0.125f,0.125f,
        -0.125f,-0.125f,0.125f,
        -0.125f,0.125f,-0.125f,
        -0.125f,-0.125f,0.125f,
        -0.125f,-0.125f,-0.125f,


        0.125f,0.125f,0.125f,
        -0.125f,0.125f,0.125f,
        0.125f,0.125f,-0.125f,
        -0.125f,0.125f,0.125f,
        0.125f,0.125f,-0.125f,
        -0.125f,0.125f,-0.125f,


        0.125f,-0.125f,0.125f,
        -0.125f,-0.125f,0.125f,
        0.125f,-0.125f,-0.125f,
        -0.125f,-0.125f,0.125f,
        0.125f,-0.125f,-0.125f,
        -0.125f,-0.125f,-0.125f


    };
    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color, GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bomb::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Bomb::tick() {
    // this->vy-=0.0005;
    this->position.x += this->vx;
    this->position.y += this->vy;
    this->position.z += this->vz;
}

