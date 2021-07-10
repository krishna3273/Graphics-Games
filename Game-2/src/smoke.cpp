#include<bits/stdc++.h>
#include "smoke.h"
#include "main.h"
using namespace std;

Smoke::Smoke(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
     
    int n=1000;
    int radius=2;
    this->count=0;
    GLfloat vertex_buffer_data[18000];
    int k=0;
    for(int i=0;i<n;i++){
        vertex_buffer_data[k++]=cos(2*3.14*i/n)*2;
        vertex_buffer_data[k++]=sin(2*3.14*i/n)*2;
        vertex_buffer_data[k++]=0;        
        vertex_buffer_data[k++]=cos(2*3.14*(i+1)/n)*2;
        vertex_buffer_data[k++]=sin(2*3.14*(i+1)/n)*2;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=cos(2*3.14*i/n)*2.2;
        vertex_buffer_data[k++]=sin(2*3.14*i/n)*2.2;
        vertex_buffer_data[k++]=0;

        vertex_buffer_data[k++]=cos(2*3.14*i/n)*2.2;
        vertex_buffer_data[k++]=sin(2*3.14*i/n)*2.2;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=cos(2*3.14*(i+1)/n)*2.2;
        vertex_buffer_data[k++]=sin(2*3.14*(i+1)/n)*2.2;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=cos(2*3.14*(i+1)/n)*2;
        vertex_buffer_data[k++]=sin(2*3.14*(i+1)/n)*2;
        vertex_buffer_data[k++]=0;
    }
    this->object = create3DObject(GL_TRIANGLES, 6000, vertex_buffer_data, color, GL_FILL);
}

void Smoke::draw(glm::mat4 VP) {
    // if(this->count<360) this->count++;
    // else this->count=0;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]); 
    // glMaterialfv(GL_FRONT, GL_SPECULAR, COLOR_GREEN);
    draw3DObject(this->object);
}

void Smoke::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Smoke::tick() {
    // this->position.x -= speed;
    // this->position.y -= speed;
}

