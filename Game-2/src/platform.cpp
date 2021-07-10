#include "platform.h"
#include "main.h"

Platform::Platform(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    GLfloat vertex_buffer_data[]={
        // -800.0f,-400.0f,800.0f,
        // 800.0f,-400.0f,800.0f,
        // 800.0f,-2.0f,800.0f,
        // -800.0f,-400.0f,800.0f,
        // 800.0f,-2.0f,800.0f,
        // -800.0f,-2.0f,800.0f,


        // -800.0f,-400.0f,-800.0f,
        // 800.0f,-400.0f,-800.0f,
        // 800.0f,-2.0f,-800.0f,
        // -800.0f,-400.0f,-800.0f,
        // 800.0f,-2.0f,-800.0f,
        // -800.0f,-2.0f,-800.0f,


        // 800.0f,-400.0f,-800.0f,
        // 800.0f,-400.0f,800.0f,
        // 800.0f,-2.0f,800.0f,
        // 800.0f,-400.0f,-800.0f,
        // 800.0f,-2.0f,800.0f,
        // 800.0f,-2.0f,-800.0f,


        // -800.0f,-400.0f,-800.0f,
        // -800.0f,-400.0f,800.0f,
        // -800.0f,-2.0f,800.0f,
        // -800.0f,-400.0f,-800.0f,
        // -800.0f,-2.0f,800.0f,
        // -800.0f,-2.0f,-800.0f,


        800.0f,-2.0f,800.0f,
        -800.0f,-2.0f,800.0f,
        800.0f,-2.0f,-800.0f,
        -800.0f,-2.0f,800.0f,
        800.0f,-2.0f,-800.0f,
        -800.0f,-2.0f,-800.0f,


        // 800.0f,-16.0f,800.0f,
        // -800.0f,-16.0f,800.0f,
        // 800.0f,-16.0f,-800.0f,
        // -800.0f,-16.0f,800.0f,
        // 800.0f,-16.0f,-800.0f,
        // -800.0f,-16.0f,-800.0f


    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Platform::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Platform::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Platform::tick() {
    // this->position.x -= speed;
    // this->position.y -= speed;
}

