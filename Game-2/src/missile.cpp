#include<bits/stdc++.h>
#include "missile.h"
#include "main.h"
using namespace std;

Missile::Missile(float x, float y,float z,float vx,float vy,float vz ,float rx,float ry,float rz,color_t color) {

    this->position = glm::vec3(x, y, z);
    this->vx=vx;
    this->vy=vy;
    this->vz=vz;
    this->rotationx=rx;
    this->rotationy=ry;
    this->rotationz=rz;
    this->render=1;
GLfloat vertex_buffer_data[]={
         0.125f,0.5f,0.125f,
         -0.125f,0.5f,0.125f,
         0.0f,1.25f,0.0f,
         0.125f,0.5f,-0.125f,
         -0.125f,0.5f,-0.125f,
         0.0f,1.25f,0.0f,
         0.125f,0.5f,0.125f,
         0.125f,0.5f,-0.125f,
         0.0f,1.25f,0.0f,
         -0.125f,0.5f,0.125f,
         -0.125f,0.5f,-0.125f,
         0.0f,1.25f,0.0f
    };
    GLfloat vertex_buffer_data1[]={
        -0.125f,0.5f,0.125f,
        0.125f,0.5f,0.125f,
        0.125f,-0.5f,0.125f,
        -0.125f,0.5f,0.125f,
        0.125f,-0.5f,0.125f,
        -0.125f,-0.5f,0.125f,


        -0.125f,0.5f,-0.125f,
        0.125f,0.5f,-0.125f,
        0.125f,-0.5f,-0.125f,
        -0.125f,0.5f,-0.125f,
        0.125f,-0.5f,-0.125f,
        -0.125f,-0.5f,-0.125f,


        0.125f,0.5f,-0.125f,
        0.125f,0.5f,0.125f,
        0.125f,-0.5f,0.125f,
        0.125f,0.5f,-0.125f,
        0.125f,-0.5f,0.125f,
        0.125f,-0.5f,-0.125f,


        -0.125f,0.5f,-0.125f,
        -0.125f,0.5f,0.125f,
        -0.125f,-0.5f,0.125f,
        -0.125f,0.5f,-0.125f,
        -0.125f,-0.5f,0.125f,
        -0.125f,-0.5f,-0.125f,


        0.125f,0.5f,0.125f,
        -0.125f,0.5f,0.125f,
        0.125f,0.5f,-0.125f,
        -0.125f,0.5f,0.125f,
        0.125f,0.5f,-0.125f,
        -0.125f,0.5f,-0.125f,


        0.125f,-0.5f,0.125f,
        -0.125f,-0.5f,0.125f,
        0.125f,-0.5f,-0.125f,
        -0.125f,-0.5f,0.125f,
        0.125f,-0.5f,-0.125f,
        -0.125f,-0.5f,-0.125f


    };
    this->object1 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, COLOR_WHITE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotatex    = glm::rotate((float) (this->rotationx * M_PI / 180.0f), glm::vec3(1,0, 0));  
    glm::mat4 rotatey    = glm::rotate((float) (this->rotationy * M_PI / 180.0f), glm::vec3(0,1, 0));  
    glm::mat4 rotatez    = glm::rotate((float) (this->rotationz * M_PI / 180.0f), glm::vec3(0,0, 1)); 
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotatey*rotatez*rotatex);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Missile::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Missile::tick() {
    // this->vy-=0.001;
    this->position.x += this->vx;
    this->position.y += this->vy;
    this->position.z += this->vz;
}

