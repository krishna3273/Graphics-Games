#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color,float v1,float v2,float radius,int type) {
    this->position = glm::vec3(x, y, 0);
    this->vx=v1;
    this->vy=v2;
    int n=20;
    this->radius=radius;
    this->type=type;
    this->rotation=0;
    GLfloat vertex_buffer_data[9*n];
    int k=0;
    for(int i=0;i<n;i++){
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=cos(2*3.14*i/n)/this->radius;
        vertex_buffer_data[k++]=sin(2*3.14*i/n)/this->radius;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=cos(2*3.14*(i+1)/n)/this->radius;
        vertex_buffer_data[k++]=sin(2*3.14*(i+1)/n)/this->radius;
        vertex_buffer_data[k++]=0;
    }
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
        // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    if(type!=0)
    Matrices.model *= translate;
    if(type==0)
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
     this->position.x += this->vx;
     if(this->type==2){
     if(this->position.y<this->radius-1) this->vy=-this->vy; 
     }
     if(this->type==1){
         if(this->position.y > -1) this->vy-=0.0007;
     }
     if(this->type==0){
         this->rotation+=2;
     }
     this->position.y +=this->vy;
}

