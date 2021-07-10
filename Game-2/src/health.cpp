#include<bits/stdc++.h>
#include "health.h"
#include "main.h"
using namespace std;

Health::Health(float x, float y,float z,float rx,float ry,float rz,color_t color) {

    this->position = glm::vec3(x, y, z);
    this->rotationx=rx;
    this->rotationy=0;
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

         
    };
    GLfloat vertex_buffer_data1[]={
            -0.1f,-0.3f,0.5f,
        0.1f,-0.3f,0.5f,
        -0.1f,0.3f,0.5f,
         0.1f,-0.3f,0.5f,
        -0.1f,0.3f,0.5f,
        0.1f,0.3f,0.5f,

        -0.3f,-0.1,0.5f,
        -0.3f,0.1f,0.5f,
        0.3f,-0.1f,0.5f,
        -0.3f,0.1f,0.5f,
        0.3f,-0.1f,0.5f,
        0.3f,0.1f,0.5f,
    };
    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data1, COLOR_DGREEN, GL_FILL);
}

void Health::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    glm::mat4 rotatey    = glm::rotate((float) (this->rotationy * M_PI / 180.0f), glm::vec3(0,1, 0));
    Matrices.model *= (translate*rotatey);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Health::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Health::tick() {
    this->rotationy+=5;
}

