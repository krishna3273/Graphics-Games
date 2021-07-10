#include<bits/stdc++.h>
#include "compass.h"
#include "main.h"

Compass::Compass(float x, float y,float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    int n=100;
    int k=0;
    GLfloat vertex_buffer_data[900];
    for(int i=0;i<n;i++){
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=cos(2*3.14*i/n);
        vertex_buffer_data[k++]=sin(2*3.14*i/n);
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=cos(2*3.14*(i+1)/n);
        vertex_buffer_data[k++]=sin(2*3.14*(i+1)/n);
        vertex_buffer_data[k++]=0;
    }

    GLfloat vertex_buffer_data3[36];
    k=0;
        vertex_buffer_data3[k++]=cos(3.14/2);
        vertex_buffer_data3[k++]=sin(3.14/2);
        vertex_buffer_data3[k++]=0;
        vertex_buffer_data3[k++]=(cos((3.14/2)+2*3.14/n)+cos(3.14/2))/2;
        vertex_buffer_data3[k++]=(sin((3.14/2)+2*3.14/n)+sin(3.14/2))/2-0.3;
        vertex_buffer_data3[k++]=0;
        vertex_buffer_data3[k++]=cos((3.14/2)+2*3.14/n);
        vertex_buffer_data3[k++]=sin((3.14/2)+2*3.14/n);
        vertex_buffer_data3[k++]=0;

        vertex_buffer_data3[k++]=cos(3.14);
        vertex_buffer_data3[k++]=sin(3.14);
        vertex_buffer_data3[k++]=0;
        vertex_buffer_data3[k++]=(cos((3.14)+2*3.14/n)+cos(3.14))/2+0.3;
        vertex_buffer_data3[k++]=(sin((3.14)+2*3.14/n)+sin(3.14))/2;
        vertex_buffer_data3[k++]=0;
        vertex_buffer_data3[k++]=cos((3.14)+2*3.14/n);
        vertex_buffer_data3[k++]=sin((3.14)+2*3.14/n);
        vertex_buffer_data3[k++]=0;


        vertex_buffer_data3[k++]=cos(3.14/2);
        vertex_buffer_data3[k++]=-sin(3.14/2);
        vertex_buffer_data3[k++]=0;
        vertex_buffer_data3[k++]=(cos((3.14/2)+2*3.14/n)+cos(3.14/2))/2;
        vertex_buffer_data3[k++]=-((sin((3.14/2)+2*3.14/n)+sin(3.14/2))/2-0.3);
        vertex_buffer_data3[k++]=0;
        vertex_buffer_data3[k++]=cos((3.14/2)+2*3.14/n);
        vertex_buffer_data3[k++]=-sin((3.14/2)+2*3.14/n);
        vertex_buffer_data3[k++]=0;

       vertex_buffer_data3[k++]=-cos(3.14);
        vertex_buffer_data3[k++]=sin(3.14);
        vertex_buffer_data3[k++]=0;
        vertex_buffer_data3[k++]=-((cos((3.14)+2*3.14/n)+cos(3.14))/2+0.3);
        vertex_buffer_data3[k++]=(sin((3.14)+2*3.14/n)+sin(3.14))/2;
        vertex_buffer_data3[k++]=0;
        vertex_buffer_data3[k++]=-cos((3.14)+2*3.14/n);
        vertex_buffer_data3[k++]=sin((3.14)+2*3.14/n);
        vertex_buffer_data3[k++]=0;
        

    GLfloat vertex_buffer_data1[]={
        -0.15f,0.0f,0.0f,
        0.15f,0.0f,0.0f,
        0.0f,0.7f,0.0f
    };
    GLfloat vertex_buffer_data2[]={
        -0.15f,0.0f,0.0f,
        0.15f,0.0f,0.0f,
        0.0f,-0.7f,0.0f
    };
    this->v=0.1;
    this->scale=1;
    this->rotationx=0;
    this->rotationy=0;
    this->rotationz=0;
    // this->count=2;
    this->object1 = create3DObject(GL_TRIANGLES, 300, vertex_buffer_data, COLOR_WHITE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_RED, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_BLACK, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data3, COLOR_LGREEN, GL_FILL);
}

void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale (glm::mat4(1.0f),glm::vec3(0.5,0.5,0.5));    // glTranslatef
    glm::mat4 translate = glm::translate (this->position);// glTranslatef
    glm::mat4 rotatey    = glm::rotate((float) (this->rotationy * M_PI / 180.0f), glm::vec3(0,1, 0));
    glm::mat4 rotatex    = glm::rotate((float) (this->rotationx * M_PI / 180.0f), glm::vec3(1,0, 0));
    glm::mat4 rotatez    = glm::rotate((float) (this->rotationz * M_PI / 180.0f), glm::vec3(0,0, 1));    
    Matrices.model *= (translate*scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object4);
    Matrices.model = glm::mat4(1.0f);
     Matrices.model *= (translate*rotatez*scale);
     MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
      draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Compass::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Compass::tick() {
}

