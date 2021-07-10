#include<bits/stdc++.h>
#include "explosion.h"
#include "main.h"
using namespace std;
Explosion::Explosion(float x, float y,float z,float radius, color_t color) {
    this->position = glm::vec3(x, y, z);
        this->count=0;
        this->radius=radius;
        this->color=color;
GLfloat vertex_buffer_data[9000];
        int k=0,n=1000;
    for(int i=0;i<n;i++){
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=cos(2*3.14*i/n)*this->radius;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=sin(2*3.14*i/n)*this->radius;
        vertex_buffer_data[k++]=cos(2*3.14*(i+1)/n)*this->radius;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=sin(2*3.14*(i+1)/n)*this->radius;
    }
    this->object = create3DObject(GL_TRIANGLES, 3000, vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Explosion::draw(glm::mat4 VP) {
    if(this->count<300) this->count=(this->count)+1;
    // else this->count=0;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]); 
    // glMaterialfv(GL_FRONT, GL_SPECULAR, COLOR_GREEN);
    if(this->count<50){
    draw3DObject(this->object);
    }
}

void Explosion::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Explosion::tick() {
    // this->position.x -= speed;
    // this->position.y -= speed;
}

