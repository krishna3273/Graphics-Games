#include<bits/stdc++.h>
#include "volcano.h"
#include "main.h"
using namespace std;

Volcano::Volcano(float x, float y,float z,float height, color_t color) {
    this->position = glm::vec3(x, y, z);
    GLfloat vertex_buffer_data[18000];
    GLfloat vertex_buffer_data1[9000];
        int k=0,n=1000;
        this->count=0;
        this->height=height;
    for(int i=0;i<n;i++){
        // vertex_buffer_data[k++]=0;
        // vertex_buffer_data[k++]=height;
        // vertex_buffer_data[k++]=0;
        // vertex_buffer_data[k++]=cos(2*3.14*i/n);
        // vertex_buffer_data[k++]=0;
        // vertex_buffer_data[k++]=sin(2*3.14*i/n);
        // vertex_buffer_data[k++]=cos(2*3.14*(i+1)/n);
        // vertex_buffer_data[k++]=0;
        // vertex_buffer_data[k++]=sin(2*3.14*(i+1)/n);
        vertex_buffer_data[k++]=cos(2*3.14*i/n)*0.6;
        vertex_buffer_data[k++]=height;
        vertex_buffer_data[k++]=sin(2*3.14*i/n)*0.6;
        vertex_buffer_data[k++]=cos(2*3.14*(i+1)/n)*0.6;
        vertex_buffer_data[k++]=height;
        vertex_buffer_data[k++]=sin(2*3.14*(i+1)/n)*0.6;
        vertex_buffer_data[k++]=cos(2*3.14*i/n)*3;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=sin(2*3.14*i/n)*3;

        vertex_buffer_data[k++]=cos(2*3.14*i/n)*3;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=sin(2*3.14*i/n)*3;
        vertex_buffer_data[k++]=cos(2*3.14*(i+1)/n)*3;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=sin(2*3.14*(i+1)/n)*3;
        vertex_buffer_data[k++]=cos(2*3.14*(i+1)/n)*0.6;
        vertex_buffer_data[k++]=height;
        vertex_buffer_data[k++]=sin(2*3.14*(i+1)/n)*0.6;
    }
    k=0;
    for(int i=0;i<n;i++){
        // random+=0.0005;
        vertex_buffer_data1[k++]=0;
        vertex_buffer_data1[k++]=0;
        vertex_buffer_data1[k++]=0;
        vertex_buffer_data1[k++]=cos(2*3.14*i/n)*5;
        vertex_buffer_data1[k++]=0;
        vertex_buffer_data1[k++]=sin(2*3.14*i/n)*5;
        vertex_buffer_data1[k++]=cos(2*3.14*(i+1)/n)*5;
        vertex_buffer_data1[k++]=0;
        vertex_buffer_data1[k++]=sin(2*3.14*(i+1)/n)*5;
    }
    this->object1 = create3DObject(GL_TRIANGLES, 6000, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3000, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    if(this->count<36) this->count++;
    else this->count=0;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]); 
    // glMaterialfv(GL_FRONT, GL_SPECULAR, COLOR_GREEN);
    draw3DObject(this->object1);
    if(this->count<18){
    draw3DObject(this->object2);
    }
}

void Volcano::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Volcano::tick() {
    // this->position.x -= speed;
    // this->position.y -= speed;
}

