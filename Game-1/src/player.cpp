#include "player.h"
#include "main.h"

Player::Player(float x, float y, color_t color,float v1,float v2) {
    this->position = glm::vec3(x, y, 0);
    this->vx=v1;
    this->vy=v2;
    this->width=0.2;
    this->length=0.2;
    GLfloat vertex_buffer_data[]={
        -0.1f,0.1f,-0.0f,
        0.1f,0.1f,0.0f,
        -0.1f,-0.1f,0.0f,
        -0.1f,-0.1f,0.0f,
        0.1f,0.1f,0.0f,
        0.1f,-0.1f,0.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);  
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::tick() {
     this->position.x += this->vx;
     if((this->position.y>-0.9 || this->vy>0)) this->position.y +=this->vy;
}

