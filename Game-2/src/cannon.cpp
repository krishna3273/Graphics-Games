#include<bits/stdc++.h>
#include "cannon.h"
#include "main.h"
using namespace std;

Cannon::Cannon(float x, float y,float z,float rx,float ry,float rz,color_t color) {

    this->position = glm::vec3(x, y, z);
    this->rotationx=rx;
    this->rotationy=ry;
    this->rotationz=rz;
    this->render=1;
    this->count=0;
    GLfloat vertex_buffer_data[]={
        -0.5f,0.5f,0.5f,
        0.5f,0.5f,0.5f,
        0.5f,-0.5f,0.5f,
        -0.5f,0.5f,0.5f,
        0.5f,-0.5f,0.5f,
        -0.5f,-0.5f,0.5f,


        -0.5f,0.5f,-0.5f,
        0.5f,0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        -0.5f,0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,


        0.5f,0.5f,-0.5f,
        0.5f,0.5f,0.5f,
        0.5f,-0.5f,0.5f,
        0.5f,0.5f,-0.5f,
        0.5f,-0.5f,0.5f,
        0.5f,-0.5f,-0.5f,


        -0.5f,0.5f,-0.5f,
        -0.5f,0.5f,0.5f,
        -0.5f,-0.5f,0.5f,
        -0.5f,0.5f,-0.5f,
        -0.5f,-0.5f,0.5f,
        -0.5f,-0.5f,-0.5f,


        0.5f,0.5f,0.5f,
        -0.5f,0.5f,0.5f,
        0.5f,0.5f,-0.5f,
        -0.5f,0.5f,0.5f,
        0.5f,0.5f,-0.5f,
        -0.5f,0.5f,-0.5f,


        0.5f,-0.5f,0.5f,
        -0.5f,-0.5f,0.5f,
        0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,0.5f,
        0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f

        // -0.125f,0.5f,0.15f,
        // 0.125f,0.5f,0.15f,
        // -0.125f,1.0f,0.05f,
        // 0.125f,0.5f,0.15f,
        // -0.125f,1.0f,0.05f,
        // 0.125f,1.0f,0.05f,

        // -0.125f,0.5f,-0.15f,
        // 0.125f,0.5f,-0.15f,
        // -0.125f,1.0f,-0.5f,
        // 0.125f,0.5f,-0.15f,
        // -0.125f,1.0f,-0.5f,
        // 0.125f,1.0f,-0.5f
        

        // 0.5f,0.5f,-0.35f,
        // 0.5f,0.5f,0.15f,
        // 0.5f,0.0f,0.15f,
        // 0.5f,0.5f,-0.35f,
        // 0.5f,0.0f,0.15f,
        // 0.5f,0.0f,-0.35f,


        // -0.5f,0.5f,-0.35f,
        // -0.5f,0.5f,0.35f,
        // -0.5f,0.0f,0.15f,
        // -0.5f,0.5f,-0.35f,
        // -0.5f,0.0f,0.15f,
        // -0.5f,0.0f,-0.35f,


        // 0.5f,0.5f,0.15f,
        // -0.5f,0.5f,0.15f,
        // 0.5f,0.5f,-0.35f,
        // -0.5f,0.5f,0.15f,
        // 0.5f,0.5f,-0.35f,
        // -0.5f,0.5f,-0.35f,


        // 0.5f,0.0f,0.15f,
        // -0.5f,0.0f,0.15f,
        // 0.5f,0.0f,-0.35f,
        // -0.5f,0.0f,0.15f,
        // 0.5f,0.0f,-0.35f,
        // -0.5f,0.0f,-0.35f

    };
    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color, GL_FILL);
}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cannon::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick() {
    
}

