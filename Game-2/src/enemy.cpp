#include "enemy.h"
#include "main.h"

Enemy::Enemy(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    GLfloat vertex_buffer_data[]={
        -0.5f,-0.5f,0.0f,
        -0.5f,0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        -0.5f,0.5f,0.0f,
        0.5f,0.5f,0.0f,
    };
int n=20;
    int radius=1;
    float ry =0.01+0.02*double(rand()) / (double(RAND_MAX) + 1.0);
    float rx =0.05-0.1*double(rand()) / (double(RAND_MAX) + 1.0);    
    this->rx=rx;
    this->ry=ry;
    GLfloat vertex_buffer_data1[18*n];
    int k=0;
    for(int i=0;i<n/2;i++){
        
        vertex_buffer_data1[k++]=cos(2*3.14*(i+1)/n)*radius;
        vertex_buffer_data1[k++]=1+sin(2*3.14*(i+1)/n)*radius;
        vertex_buffer_data1[k++]=-1;
        vertex_buffer_data1[k++]=cos(2*3.14*i/n)*radius;
        vertex_buffer_data1[k++]=1+sin(2*3.14*i/n)*radius;
        vertex_buffer_data1[k++]=0;
        vertex_buffer_data1[k++]=cos(2*3.14*(i+1)/n)*radius;
        vertex_buffer_data1[k++]=1+sin(2*3.14*(i+1)/n)*radius;
        vertex_buffer_data1[k++]=0;


         vertex_buffer_data1[k++]=cos(2*3.14*i/n)*radius;
        vertex_buffer_data1[k++]=1+sin(2*3.14*i/n)*radius;
        vertex_buffer_data1[k++]=0;
        vertex_buffer_data1[k++]=cos(2*3.14*i/n)*radius;
        vertex_buffer_data1[k++]=1+sin(2*3.14*i/n)*radius;
        vertex_buffer_data1[k++]=-1;
        vertex_buffer_data1[k++]=cos(2*3.14*(i+1)/n)*radius;
        vertex_buffer_data1[k++]=1+sin(2*3.14*(i+1)/n)*radius;
        vertex_buffer_data1[k++]=-1;
    }
    GLfloat vertex_buffer_data2[]={
        0.0f,0.5f,0.0f,
        -1.0f,1.0f,0.0f,
        -0.6f,1.0f,0.0f,
        0.0f,0.5f,0.0f,
        1.0f,1.0f,0.0f,
        0.6f,1.0f,0.0f,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_LGREEN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data1, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, COLOR_DGREEN, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale (glm::mat4(1.0f),glm::vec3(2,2,2)); 
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);    
}

void Enemy::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemy::tick() {
    this->position.x+=rx;
    this->position.y+=ry;
}

