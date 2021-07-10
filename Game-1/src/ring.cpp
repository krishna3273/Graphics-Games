#include "ring.h"
#include "main.h"

Ring::Ring(float x, float y, color_t color,float radius) {
    this->position = glm::vec3(x, y, 0);
    int n=20;
    this->radius=radius;
    GLfloat vertex_buffer_data[9*n];
    int k=0;
    for(int i=0;i<n/2;i++){
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=cos(2*3.14*i/n)*this->radius;
        vertex_buffer_data[k++]=sin(2*3.14*i/n)*this->radius;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=cos(2*3.14*(i+1)/n)*this->radius;
        vertex_buffer_data[k++]=sin(2*3.14*(i+1)/n)*this->radius;
        vertex_buffer_data[k++]=0;
    }
    this->object = create3DObject(GL_TRIANGLES, n*3/2, vertex_buffer_data, color, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ring::tick() {
     
}

