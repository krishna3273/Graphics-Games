#include "wall.h"
#include "main.h"

Wall::Wall(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    GLfloat vertex_buffer_data[]={
        
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Wall::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Wall::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Wall::tick() {
    // this->position.x -= speed;
    // this->position.y -= speed;
}

