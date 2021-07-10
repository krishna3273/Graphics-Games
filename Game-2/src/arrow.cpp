#include<bits/stdc++.h>
#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y,float z,color_t color,int type) {
    this->position = glm::vec3(x, y, z);
    GLfloat vertex_buffer_data[]={
        -0.5f,-0.5f,0.0f,
        -0.5f,0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        -0.5f,0.5f,0.0f,
        0.5f,0.5f,0.0f,
    };
    GLfloat vertex_buffer_data1[]={
        -0.75f,-0.5f,0.0f,
        0.75f,-0.5f,0.0f,
        0.0f,-1.0f,0.0f
    };
    this->v=0.1;
    this->scale=1;
    this->type=type;
    this->rotationx=0;
    this->rotationy=0;
    this->rotationz=0;
    // this->count=2;
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
}

void Arrow::draw(glm::mat4 VP,float x1,float y1,float z1) {
    float scale1[2]={abs(this->position.x-x1)/20,abs(this->position.z-z1)/20};
    float* i;
    i=std::max_element(scale1,scale1+2);
    float scale2=(*i);
    if(scale2<1) scale2=1;
    this->scale=scale2;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);// glTranslatef
    glm::mat4 scale = glm::scale (glm::mat4(1.0f),glm::vec3(scale2,scale2,scale2));    // glTranslatef
    glm::mat4 rotatey    = glm::rotate((float) (this->rotationy * M_PI / 180.0f), glm::vec3(0,1, 0));
    glm::mat4 rotatex    = glm::rotate((float) (this->rotationx * M_PI / 180.0f), glm::vec3(1,0, 0));
    glm::mat4 rotatez    = glm::rotate((float) (this->rotationz * M_PI / 180.0f), glm::vec3(0,0, 1));    
    Matrices.model *= (translate*rotatey*scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Arrow::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Arrow::tick() {
    if(this->position.y<1+this->scale) this->v=-this->v;
    if(this->position.y>6) this->v=-this->v;
    this->position.y +=this->v;
    this->rotationy+=10;
}

