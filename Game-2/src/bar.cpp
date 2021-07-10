#include "bar.h"
#include "main.h"

Bar::Bar(float x, float y,float z, color_t color,color_t color1,color_t color2,color_t color3) {
    this->position = glm::vec3(x, y, z);
    GLfloat vertex_buffer_data[]={
        0.0f,0.0f,0.0f,
        0.25f,0.0f,0.0f,
        0.25f,0.5f,0.0f,
        0.0f,0.0f,0.0f,
        0.25f,0.5f,0.0f,
        0.0f,0.5f,0.0f
    };
    GLfloat vertex_buffer_data1[]={
        0.0f,0.5f,0.0f,
        0.25f,0.5f,0.0f,
        0.25f,1.0f,0.0f,
        0.0f,0.5f,0.0f,
        0.25f,1.0f,0.0f,
        0.0f,1.0f,0.0f
    };
    GLfloat vertex_buffer_data2[]={
        0.0f,1.0f,0.0f,
        0.25f,1.0f,0.0f,
        0.25f,1.5f,0.0f,
        0.0f,1.0f,0.0f,
        0.25f,1.5f,0.0f,
        0.0f,1.5f,0.0f
    };
    GLfloat vertex_buffer_data3[]={
        0.0f,1.5f,0.0f,
        -0.2f,1.6f,0.0f,
        -0.2f,1.4f,0.0f,
    };
    float reading=0;
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, color1, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, color2, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data3, color3, GL_FILL);
}

void Bar::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (glm::vec3(this->position.x,this->position.y-this->reading,this->position.z));    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate;
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object4);
}

void Bar::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Bar::tick(float x) {
    this->reading+=x;
}
void Bar::tick1(float x) {
    this->reading=x;
}
