#include<iostream>
#include "plane.h"
#include "main.h"
using namespace std;

Plane::Plane(float x, float y, float z,color_t color,float v1,float v2) {
    this->position = glm::vec3(x, y, z);
    this->vx=v1;
    this->vy=v2;
    this->vz=0;
    this->width=0.2;
    this->length=0.2;
    this->rotationx=270;
    this->rotationy=0;
    this->rotationz=0;
    GLfloat vertex_buffer_data[]={
         1.0f,0.0f,1.0f,
         -1.0f,0.0f,1.0f,
         0.0f,2.0f,0.0f,

         1.0f,-2.0f,1.0f,
         -1.0f,-2.0f,1.0f,
         0.0f,-4.0f,0.0f
    };
    GLfloat vertex_buffer_data1[]={
     1.0f,0.0f,-1.0f,
         -1.0f,0.0f,-1.0f,
         0.0f,2.0f,0.0f,

         1.0f,-2.0f,-1.0f,
         -1.0f,-2.0f,-1.0f,
         0.0f,-4.0f,0.0f
    };
    GLfloat vertex_buffer_data2[]={
     1.0f,0.0f,1.0f,
         1.0f,0.0f,-1.0f,
         0.0f,2.0f,0.0f,

         1.0f,-2.0f,1.0f,
         1.0f,-2.0f,-1.0f,
         0.0f,-4.0f,0.0f
    };
    GLfloat vertex_buffer_data3[]={
     -1.0f,0.0f,1.0f,
         -1.0f,0.0f,-1.0f,
         0.0f,2.0f,0.0f,

         -1.0f,-2.0f,1.0f,
         -1.0f,-2.0f,-1.0f,
         0.0f,-4.0f,0.0f
    };
    GLfloat vertex_buffer_data4[]={
     -1.0f,0.0f,1.0f,
     1.0f,0.0f,1.0f,
     -1.0f,-2.0f,1.0f,
     -1.0f,-2.0f,1.0f,
     1.0f,0.0f,1.0f,
     1.0f,-2.0f,1.0f,


     -1.0f,0.0f,-1.0f,
     1.0f,0.0f,-1.0f,
     -1.0f,-2.0f,-1.0f,
     -1.0f,-2.0f,-1.0f,
     1.0f,0.0f,-1.0f,
     1.0f,-2.0f,-1.0f,


     -1.0f,-2.0f,1.0f,
     1.0f,-2.0f,1.0f,
     -1.0f,-2.0f,-1.0f,
     -1.0f,-2.0f,-1.0f,
     1.0f,-2.0f,1.0f,
     1.0f,-2.0f,-1.0f,


     1.0f,-2.0f,1.0f,
     1.0f,-2.0f,-1.0f,
     1.0f,0.0f,-1.0f,
     1.0f,-2.0f,1.0f,
     1.0f,0.0f,-1.0f,
     1.0f,0.0f,1.0f,


     -1.0f,-2.0f,1.0f,
     -1.0f,-2.0f,-1.0f,
     -1.0f,0.0f,-1.0f,
     -1.0f,-2.0f,1.0f,
     -1.0f,0.0f,-1.0f,
     -1.0f,0.0f,1.0f
    };


    GLfloat vertex_buffer_data5[]={
         1.0f,0.0f,0.0f,
         1.0f,-2.0f,0.0f,
         4.0f,-1.0f,0.0f,
         -1.0f,0.0f,0.0f,
         -1.0f,-2.0f,0.0f,
         -4.0f,-1.0f,0.0f,
    };
    int  n=20;
    GLfloat vertex_buffer_data6[9*n];
    int k=0;
    for(int i=0;i<n;i++){
        vertex_buffer_data6[k++]=0.0f;
        vertex_buffer_data6[k++]=2.0f;
        vertex_buffer_data6[k++]=0.0f;
        vertex_buffer_data6[k++]=cos(2*3.14*i/n)*1.2;
        vertex_buffer_data6[k++]=2.0f;
        vertex_buffer_data6[k++]=sin(2*3.14*i/n)*1.2;
        vertex_buffer_data6[k++]=cos(2*3.14*(i+1)/n)*1.2;
        vertex_buffer_data6[k++]=2.0f;
        vertex_buffer_data6[k++]=sin(2*3.14*(i+1)/n)*1.2;
    }
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, COLOR_BRED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, COLOR_GREEN, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data3, COLOR_RED, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 30, vertex_buffer_data4, COLOR_BLACK, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data5, COLOR_YELLOW, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data6, COLOR_PURPLE, GL_FILL);
}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotatex    = glm::rotate((float) (this->rotationx * M_PI / 180.0f), glm::vec3(1,0, 0));  
    glm::mat4 rotatey    = glm::rotate((float) (this->rotationy * M_PI / 180.0f), glm::vec3(0,1, 0));  
    glm::mat4 rotatez    = glm::rotate((float) (this->rotationz * M_PI / 180.0f), glm::vec3(0,0, 1));      
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate*rotatey*rotatex*rotatez);
    Matrices.model *= (translate*rotatey*rotatez*rotatex);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
}

void Plane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Plane::tick() {
     this->position.z -= 0.05 ;
    //  this->position.y+=this->vy;
    //  cout<<this->rotationz<<endl;
}

