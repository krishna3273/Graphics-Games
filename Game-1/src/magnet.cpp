#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    GLfloat vertex_buffer_data[126]={
        0.0f,0.0f,0.0f,
        -0.1f,0.0f,0.0f,
        -0.1f,-0.3f,0,
        0.0f,0.0f,0.0f,
        -0.1f,-0.3f,0.0f,
        0.0f,-0.3f,0.0f,
        0.1f,-0.3f,0.0f,
        0.2f,-0.3f,0.0f,
        0.1f,0.0f,0.0f,
        0.1f,0.0f,0.0f,
        0.2f,-0.3f,0.0f,
        0.2f,0.0f,0.0f,
    };
        int n=20;
    int k=36;
    for(int i=0;i<10;i++){
        vertex_buffer_data[k++]=0.05;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0.05+(cos(2*3.14*i/n)/20)*3;
        vertex_buffer_data[k++]=(sin(2*3.14*i/n)/20)*3;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0.05+(cos(2*3.14*(i+1)/n)/20)*3;
        vertex_buffer_data[k++]=(sin(2*3.14*(i+1)/n)/20)*3;
        vertex_buffer_data[k++]=0;
    }
    this->object = create3DObject(GL_TRIANGLES, 42, vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
     
}

