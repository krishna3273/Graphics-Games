#include "main.h"
#include "timer.h"
#include "player.h"
#include "wall.h"
#include "platform.h"
#include "fireline.h"
#include "ball.h"
#include "boom.h"
#include "fireball.h"
#include "magnet.h"
#include "powerup1.h"
#include "powerup2.h"
#include "ring.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Player player;
vector<Powerup1> powerup1;
vector<Powerup2> powerup2;
Wall wall;
Platform plat;
vector<Boom> boom;
vector<Magnet> magnets;
vector<Ball> coins;
vector<Ball> waterballs;
vector<Fireline> firelines;
vector<Fireball> fireballs;
Ring ring;
float angle=0;
int score;
int coinsc;
int dist;
int bonus=0;
char title[100];
int wcount=0;
int inside=0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

// ---------------------------------------------------------------------------------
int firecollide(float x3,float y3,float d,int type){
    int collide=0;
for(int i=0;i<firelines.size();i++){
float x1=firelines[i].position.x;
float y1=firelines[i].position.y;
// float x3=player.position.x;
// float y3=player.position.y;
// float d1=pow(pow(x3-x1,2)+pow(y3-y1,2),0.5);
// float d2=pow(pow(x3-x2,2)+pow(y3-y2,2),0.5);
// float d3=pow(pow(firelines[i].x_shi,2)+pow(firelines[i].y_shi,2),0.5);
// if(abs(d1+d2-d3)<0.07) quit(window);
float x_base=firelines[i].x_shi/20;
float y_base=firelines[i].y_shi/20;
for(int j=0;j<=20;j++){
    float t1=x1+j*x_base;
    float t2=y1+j*y_base;
    float d_temp=pow(pow(x3-t1,2)+pow(y3-t2,2),0.5);
    if(d_temp<d+0.1 && firelines[i].active==1 && type==1) {collide=1;}
    if(d_temp<d+0.1 && firelines[i].active==1 && type==2) {
        firelines.erase(firelines.begin()+i);
        // firelines[i].active=0;
        // collide=1;
        return 1;
}
}
}
for(int i=0;i<fireballs.size();i++){
float x1=fireballs[i].f1.position.x;
float y1=fireballs[i].f1.position.y;
float x_base=fireballs[i].f1.x_shi/20;
float y_base=fireballs[i].f1.y_shi/20;
for(int j=0;j<=20;j++){
    float t1=x1+j*x_base;
    float t2=y1+j*y_base;
    float d_temp=pow(pow(x3-t1,2)+pow(y3-t2,2),0.5);
    if(d_temp<d+0.1 && fireballs[i].f1.active==1 && type==1) {collide=1;}
    if(d_temp<d+0.1 && fireballs[i].f1.active==1 && type==2) {
        fireballs.erase(fireballs.begin()+i);
        return 1;
}
}
}
for(int i=0;i<fireballs.size();i++){
float x1=fireballs[i].f2.position.x;
float y1=fireballs[i].f2.position.y;
float x_base=fireballs[i].f2.x_shi/20;
float y_base=fireballs[i].f2.y_shi/20;
for(int j=0;j<=20;j++){
    float t1=x1+j*x_base;
    float t2=y1+j*y_base;
    float d_temp=pow(pow(x3-t1,2)+pow(y3-t2,2),0.5);
    if(d_temp<d+0.1 && fireballs[i].f2.active==1 && type==1) {collide=1;}
    if(d_temp<d+0.1 && fireballs[i].f2.active==1 && type==2) {
        fireballs.erase(fireballs.begin()+i);
        return 1;
}
}
}
return collide;
}
// ---------------------------------------------------------------------------------
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 0, 0, 5 );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    wall.draw(VP);
    plat.draw(VP);
    ring.draw(VP);
    player.draw(VP);

    for(int i=0;i<powerup1.size();i++){
    powerup1[i].draw(VP);
    }
    for(int i=0;i<powerup2.size();i++){
    powerup2[i].draw(VP);
    }
    for(int i=0;i<boom.size();i++){
    boom[i].draw(VP);
    }
    for(int i=0;i<60;i++){
        coins[i].draw(VP);
    }
    for(int i=0;i<magnets.size();i++){
        magnets[i].draw(VP);
    }
    for(int i=0;i<waterballs.size();i++){
        waterballs[i].draw(VP);
    }
    for(int i=0;i<firelines.size();i++){
        firelines[i].draw(VP);
    }
    for(int i=0;i<fireballs.size();i++){
        fireballs[i].draw(VP);
    }
    // fire.draw(VP);
    // ball.draw(VP);
    // boom.draw(VP);
    // magnet.draw(VP);
}


int  collision(){
    int d1;
for(int i =0;i<magnets.size();i++){
    float x_diff=magnets[i].position.x-player.position.x+0.05;
    float y_diff=magnets[i].position.y-player.position.y;
    if(x_diff*x_diff+y_diff*y_diff <= 4){
        bounding_box_t* a=new bounding_box_t(magnets[i].position.x+0.05,magnets[i].position.y-0.075,0.3,0.45);
        bounding_box_t* b=new bounding_box_t(player.position.x,player.position.y,player.width,player.length);
        d1=detect_collision(a,b);
         if(!detect_collision(a,b)){
        int vx=-1,vy=-1;
        if(x_diff>0) vx =1;
        if(y_diff>=0) vy=1;
        player.vx+=vx*0.003;
        player.vy+=vy*0.0004;
        }
        else {
            player.vy=0;
        }
    }
}
for(int i=0;i<60;i++){
        bounding_box_t* a=new bounding_box_t(player.position.x,player.position.y,player.width,player.length);
        bounding_box_t* b=new bounding_box_t(coins[i].position.x,coins[i].position.y,2/coins[i].radius,2/coins[i].radius);
        if(detect_collision(a,b)){
            coinsc+=1; 
            coins.erase(coins.begin()+i);
        }
    }
for(int i=0;i<waterballs.size();i++){
    if(waterballs[i].position.y<1/waterballs[i].radius-1) waterballs.erase(waterballs.begin()+i);
}

for(int i=0;i<boom.size();i++){
     bounding_box_t* a=new bounding_box_t(player.position.x,player.position.y,player.width,player.length);
    bounding_box_t* b=new bounding_box_t(boom[i].position.x,boom[i].position.y,boom[i].width,boom[i].height);
    if(detect_collision(a,b)) quit(window);
}


for(int i=0;i<powerup1.size();i++){
    bounding_box_t* a=new bounding_box_t(powerup1[i].position.x+0.0875,powerup1[i].position.y+0.15,powerup1[i].width,powerup1[i].height);
     bounding_box_t* b=new bounding_box_t(player.position.x,player.position.y,player.width,player.length);
    if(detect_collision(a,b)){
        powerup1.erase(powerup1.begin()+i);
        // screen_center_x+=10;
        player.position.x+=10;
    } 
}
for(int i=0;i<powerup2.size();i++){
    bounding_box_t* a=new bounding_box_t(powerup2[i].position.x+0.125,powerup2[i].position.y+0.15,powerup2[i].width,powerup2[i].height);
     bounding_box_t* b=new bounding_box_t(player.position.x,player.position.y,player.width,player.length);
    if(detect_collision(a,b)){
        bonus+=100;
        powerup2.erase(powerup2.begin()+i);
    } 
}

if(firecollide(player.position.x,player.position.y,0.07,1)) quit(window);
for(int i=0;i<waterballs.size();i++){
    if(firecollide(waterballs[i].position.x,waterballs[i].position.y,1/waterballs[i].radius,2)){
        waterballs.erase(waterballs.begin()+i);
    }
}
return d1;
}


void water(){
if(wcount<=3){
Ball w=Ball(player.position.x+(player.width/2),player.position.y,COLOR_BLUE,player.vx+0.05,0,12,1);
waterballs.push_back(w);
}
wcount++;
}






void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up    = glfwGetKey(window,GLFW_KEY_UP);
//////////////////////////////////////////////////////////////////////////////////////////////////
     player.vx=0;
     if(inside==1) player.vy=0;
if(left && player.position.x>-3.5){
    // if(player.position.x<=screen_center_x) screen_center_x-=0.05;
    if(inside==0)
    player.vx=-0.05;
     if(inside==1){
        angle=atan2(player.position.y-0.5,10-player.position.x);
        player.vx=-0.01*sin(angle);
        player.vy=-0.01*cos(angle);
    }
}
if(right && player.position.x<100){
    // if(player.position.x>=screen_center_x) screen_center_x+=0.05;
    if(inside==0)
    player.vx=0.05;
    if(inside==1){
        angle=atan2(player.position.y-0.5,10-player.position.x);
        player.vx=0.01*sin(angle);
        player.vy=0.01*cos(angle);
    }
}
if(up){
    if(!(player.position.x>=9 && player.position.x<=11 && player.position.y>=0.5 && player.position.y<=1.6)){
    if(player.vy<0) player.vy=0;
    player.vy+=0.001;
    }
        
    
}
if(player.position.y>3.75) player.vy=0;
///////////////////////////////////////////////////////////////////////////////////////////////////

}


void tick_elements() {
    if(!(player.position.x>=9 && player.position.x<=11 && player.position.y>=0.5 && player.position.y<=1.5)){
    player.vy-=0.0005;
    inside=0;
    }
    if(player.position.x>=9 && player.position.x<=11 && player.position.y>=0.5 && player.position.y<=1.5 && inside==0){
        inside=1;
        player.vy=0;
        player.position.x=9;
        player.position.y=0.5;
    }
    collision();
    for(int i=0;i<fireballs.size();i++){
        fireballs[i].tick();
    }
    for(int i=0;i<coins.size();i++){
        coins[i].tick();
    }
    for(int i=0;i<powerup1.size();i++){
        if(powerup1[i].position.x-screen_center_x<5)
    powerup1[i].tick();
    }
    for(int i=0;i<powerup2.size();i++){
        if(powerup2[i].position.x-screen_center_x<5)
    powerup2[i].tick();
    }
    player.tick();
    // ball.vy-=0.0006; 
    // ball.tick();
    for(int i=0;i<boom.size();i++){
        if(boom[i].position.x-screen_center_x<5){
    if(boom[i].dir==0) boom[i].vx-=0.001;
    if(player.position.x-boom[i].position.x>1.5 && boom[i].vx<0) {boom[i].dir=1;boom[i].vx=0;}
    if(boom[i].dir==1) boom[i].vx+=0.001; 
    boom[i].tick();
        }
    }
    // fire.tick();
    for(int i=0;i<waterballs.size();i++){
        waterballs[i].tick();
    }
    if(player.position.x-screen_center_x>1 && screen_center_x+4<100) screen_center_x+=0.05;
    if(screen_center_x-player.position.x>1 && screen_center_x-4>-4) screen_center_x-=0.05;
    dist=round(player.position.x);
    score=coinsc*10+dist+bonus;
    sprintf(title,"Score: %d      Coins: %d          Distance: %d",score,coinsc,dist);
    glfwSetWindowTitle(window,title);
    reset_screen();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    player       =Player(0, -0.8, COLOR_RED,0,0);
    wall         =Wall(0,0,COLOR_GREEN);
    plat         =Platform(0,0,COLOR_BLACK);
    ring         =Ring(10,0.5,COLOR_BLACK,1);
     Powerup1  p1   =Powerup1(15,2.5,COLOR_PURPLE,-0.007,0);
       powerup1.push_back(p1);
       for(int i=0;i<10;i++){
          float r =50-double(rand()) / (double(RAND_MAX) + 1.0);
        float x=powerup1[i-1].position.x;
        float y=3.75*double(rand()) / (double(RAND_MAX) + 1.0);

        Powerup1 m=Powerup1(x+r,y,COLOR_PURPLE,-0.0007,0);
        powerup1.push_back(m); 
       } 
       Powerup2  p2   =Powerup2(10,2.5,COLOR_BRED,-0.04,0);
       powerup2.push_back(p2);
       for(int i=0;i<10;i++){
          float r =20-double(rand()) / (double(RAND_MAX) + 1.0);
        float x=powerup2[i-1].position.x;
        float y=3*double(rand()) / (double(RAND_MAX) + 1.0);

        Powerup2 m=Powerup2(x+r,y,COLOR_BRED,-0.04,0);
        powerup2.push_back(m); 
       } 
    Fireline f=Fireline(8,3,COLOR_ORANGE,3.14/4,0,0);
    firelines.push_back(f);
    for(int i=0;i<30;i++){
        float r =20-double(rand()) / (double(RAND_MAX) + 1.0);
        float x=firelines[i-1].position.x;
        float y=2+double(rand()) / (double(RAND_MAX) + 1.0);
        float ar=1-double(rand()) / (double(RAND_MAX) + 1.0);
        Fireline f=Fireline(x+r,y,COLOR_ORANGE,3.14*ar/2,0,0);
        Fireball b=Fireball(x+r+5,y,COLOR_ORANGE,0.008);
        fireballs.push_back(b);
        firelines.push_back(f);
        // firelines.push_back(b.f1);
        // firelines.push_back(b.f2);
    }

     Boom b=Boom(10,3,COLOR_BLACK,0,-0.007);
     boom.push_back(b);
     for(int i=1;i<10;i++){
        float r =30-double(rand()) / (double(RAND_MAX) + 1.0);
        float x=boom[i-1].position.x;
        float y=3.75*double(rand()) / (double(RAND_MAX) + 1.0);

        Boom m=Boom(x+r,y,COLOR_BLACK,0,-0.007);
        boom.push_back(m);
    }
     Ball c=Ball(2,3,COLOR_BLUE,0,0,10,0);
    coins.push_back(c);
    for(int i=1;i<60;i++){
        float r =3-double(rand()) / (double(RAND_MAX) + 1.0);
        float x=coins[i-1].position.x;
        float y=1+2*double(rand()) / (double(RAND_MAX) + 1.0);

        color_t rcolor[3]={COLOR_BLUE,COLOR_YELLOW,COLOR_ORANGE};
        int r1=rand()%3;
        Ball c=Ball(x+r,y,rcolor[r1],0,0,10,0);
        coins.push_back(c);
    }
    Magnet m=Magnet(2,0,COLOR_BRED);
    magnets.push_back(m);
    for(int i=1;i<10;i++){
        float r =30-double(rand()) / (double(RAND_MAX) + 1.0);
        float x=magnets[i-1].position.x;
        float y=3*double(rand()) / (double(RAND_MAX) + 1.0);

        Magnet m=Magnet(x+r,y,COLOR_BRED);
        magnets.push_back(m);
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t* a, bounding_box_t* b) {
    return (abs(a->x - b->x) * 2 < (a->width + b->width)) &&
           (abs(a->y - b->y) * 2 < (a->height + b->height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
