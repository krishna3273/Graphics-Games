#include "fireline.h"
#include "main.h"

Fireline::Fireline(float x, float y, color_t color,float angle,float vx,float vy) {
    float r=2;
    this->position = glm::vec3(x, y, 0);
    this->vx=vx;
    this->vy=vy;
    int n=20;
    this->active=1;
    this->color=color;
    GLfloat vertex_buffer_data[18*n+9];
    int k=0;
    float x_shi=-r*sin(angle);
    float y_shi=-r*cos(angle);
    this->x_shi=x_shi;
    this->y_shi=y_shi;
    for(int i=0;i<n;i++){
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=cos(2*3.14*i/n)/10;
        vertex_buffer_data[k++]=sin(2*3.14*i/n)/10;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=cos(2*3.14*(i+1)/n)/10;
        vertex_buffer_data[k++]=sin(2*3.14*(i+1)/n)/10;
        vertex_buffer_data[k++]=0;
    }
    for(int i=0;i<n;i++){
        vertex_buffer_data[k++]=x_shi;
        vertex_buffer_data[k++]=y_shi;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=x_shi+cos(2*3.14*i/n)/10;
        vertex_buffer_data[k++]=y_shi+sin(2*3.14*i/n)/10;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=x_shi+cos(2*3.14*(i+1)/n)/10;
        vertex_buffer_data[k++]=y_shi+sin(2*3.14*(i+1)/n)/10;
        vertex_buffer_data[k++]=0;
    }
    vertex_buffer_data[k++]=x_shi;
        vertex_buffer_data[k++]=y_shi;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=x_shi/2;
        vertex_buffer_data[k++]=y_shi/2+0.1;
        vertex_buffer_data[k++]=0;
        
    this->object = create3DObject(GL_TRIANGLES, 6*n+3, vertex_buffer_data, this->color, GL_FILL);
}

void Fireline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Fireline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fireline::tick(){
    this->position.y+=vy;
}


