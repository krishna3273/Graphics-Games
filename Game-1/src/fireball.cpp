#include "fireball.h"
#include "main.h"

Fireball::Fireball(float x, float y, color_t color,float v){
    this->f1=Fireline(x,y,color,3.14/2,0,v);
    this->f2=Fireline(x,y-1,color,3.14/2,0,-v);
    this->centre=y-0.5;
}

void Fireball::draw(glm::mat4 VP){
    this->f1.draw(VP);
    this->f2.draw(VP);
}

void Fireball::tick(){
    if(this->f1.position.y < this->centre || this->f1.position.y > this->centre+0.5) this->f1.vy=-this->f1.vy ;
    if(this->f2.position.y > this->centre || this->f2.position.y < this->centre-0.5) this->f2.vy=-this->f2.vy;
    f1.tick();
    f2.tick();

}