#include<bits/stdc++.h>
#include "ground.h"
#include "main.h"
using namespace std;

Ground::Ground(float x, float y,float z,float radius, color_t color) {
    this->position = glm::vec3(x, y, z);
    GLfloat vertex_buffer_data[9000];
    GLfloat vertex_buffer_data1[9000];
        int k=0,n=1000;
        float random=0;
        this->radius=radius;
    for(int i=0;i<n;i++){
        random=((float)rand() / RAND_MAX)*0.5;
        // random+=0.0005;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=radius*cos(2*3.14*i/n)+random;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=radius*sin(2*3.14*i/n)+random;
        vertex_buffer_data[k++]=radius*cos(2*3.14*(i+1)/n)+random;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=radius*sin(2*3.14*(i+1)/n)+random;
    }
    this->object = create3DObject(GL_TRIANGLES, 3000, vertex_buffer_data, color, GL_FILL);
}

void Ground::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ground::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ground::tick() {
    // this->position.x -= speed;
    // this->position.y -= speed;
}

