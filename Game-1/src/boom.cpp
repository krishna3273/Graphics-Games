#include "boom.h"
#include "main.h"

Boom::Boom(float x, float y, color_t color,float v1,float v2) {
    this->position = glm::vec3(x, y, 0);
    this->vx=v1;
    this->vy=v2;
    this->dir=0;
    this->height=sin(3.14/12);
    this->width=cos(3.14/12)/2;
    this->rotation=0;
    int n=20;
    GLfloat vertex_buffer_data[18];
    int k=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=cos(3.14/20)*4/5;
        vertex_buffer_data[k++]=sin(3.14/20)*4/5;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=cos(3.14/12)*4/5;
        vertex_buffer_data[k++]=sin(3.14/12)*4/5;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=cos(-3.14/20)*4/5;
        vertex_buffer_data[k++]=sin(-3.14/20)*4/5;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=cos(-3.14/12)*4/5;
        vertex_buffer_data[k++]=sin(-3.14/12)*4/5;
        vertex_buffer_data[k++]=0;
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Boom::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 1));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boom::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boom::tick() {
    this->rotation+=1.2;
    if(this->position.y<=-1) this->vy=0;
     this->position.y += this->vy;
     this->position.x += this->vx;
}

