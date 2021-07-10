#include "powerup1.h"
#include "main.h"

Powerup1::Powerup1(float x, float y, color_t color,float v1,float v2) {
    this->position = glm::vec3(x, y, 0);
    this->vx=v1;
    this->vy=v2;
    int n=20;
    this->radius=0.075;
    this->width=0.175;
    this->height=0.3;
    GLfloat vertex_buffer_data[117];
    int k=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0.1;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0.3;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0.1;
        vertex_buffer_data[k++]=0.3;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0.1;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0.3;
        vertex_buffer_data[k++]=0;
        for(int i=-5;i<=5;i++){
        vertex_buffer_data[k++]=0.1;
        vertex_buffer_data[k++]=0.225;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0.1+3*(cos(2*3.14*i/n))/40;
        vertex_buffer_data[k++]=0.225+3*(sin(2*3.14*i/n))/40;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0.1+3*(cos(2*3.14*(i+1)/n))/40;
        vertex_buffer_data[k++]=0.225+3*(sin(2*3.14*(i+1)/n)/40);
        vertex_buffer_data[k++]=0;
    }
    this->object = create3DObject(GL_TRIANGLES, 39, vertex_buffer_data, color, GL_FILL);
}

void Powerup1::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Powerup1::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Powerup1::tick() {
     this->position.x += this->vx;
     if(this->position.y>-1) this->vy-=0.0007; 
     if(this->position.y<-1 || this->position.y>3.45) this->vy=-this->vy; 
     
     this->position.y +=this->vy;
}

