#include "main.h"
#include "timer.h"
#include "plane.h"
#include "wall.h"
#include "platform.h"
#include "ground.h"
#include "volcano.h"
#include "missile.h"
#include "bomb.h"
#include "cannon.h"
#include "smoke.h"
#include "fuel.h"
#include "arrow.h"
#include "enemy.h"
#include "explosion.h"
#include "bar.h"
#include "compass.h"
#include "health.h"
using namespace std;


GLMatrices Matrices,M1;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

glm::vec3 eye, target, up;
glm::vec3 eye1(2,2,5);
glm::vec3 tar1(2,3,0);
glm::vec3 up1(0,1,0);


char title[100];
float score=0;
float h=10;
float initime;
float cx;
float cy;
Plane player;
Plane p1;
Wall wall;
Platform plat;
Bar bar;
Bar altitude;
int finish=0;
vector<Fuel> fuel;
vector<Health> health;
vector<Ground> grounds;
vector<Cannon> cannons;
vector<Volcano> volcanos;
vector<Smoke> smokes;
Arrow arrow;
Compass compass;
Bomb bombs[1000];
Missile missiles[1000];
vector<Enemy> enemies;
vector<Bomb> bombs1;
vector<Explosion> explosions;
coordinates checkpoints[100];
int ccount=0;
int vno=1;
int bsize=0;
int msize=0;
int tview=0;
int roll=0;
float bangle=0;
double mousex,mousey;
float ax,ay,radius=7;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
Timer t60(1.0 / 60);


//function for changing views
void changeveiw(){
    if(vno!=4) tview=0;
if(vno==1){
    eye=glm::vec3 ( player.position.x-5*sin(player.rotationy*M_PI/180.0f), player.position.y+cos(270*M_PI/180.0f), player.position.z-5*cos(player.rotationy*M_PI/180.0f) );
    target=glm::vec3 ( player.position.x-20*sin(player.rotationy*M_PI/180.0f), player.position.y+2, player.position.z-20*cos(player.rotationy*M_PI/180.0f) );
    up=glm::vec3 (0, 1,0 );
}
if(vno==2){
    eye=glm::vec3 ( player.position.x, player.position.y+80, player.position.z );
    target=glm::vec3 ( player.position.x, player.position.y, player.position.z );
    up=glm::vec3 (0, 0,-1 );
}
if(vno==3){
    eye=glm::vec3 ( player.position.x+15*sin(player.rotationy*M_PI/180.0f), player.position.y+cos(270*M_PI/180.0f), player.position.z+15*cos(player.rotationy*M_PI/180.0f) );
    target=glm::vec3 ( player.position.x-2*sin(player.rotationy*M_PI/180.0f), player.position.y, player.position.z-2*cos(player.rotationy*M_PI/180.0f) );
    up=glm::vec3 (0, 1,0 );
}

if(vno==0){
    eye=glm::vec3 ( 0,player.position.y, 20 );
    target=glm::vec3 (0, player.position.y,-30 );
    up=glm::vec3 (0, 1,0 );
}

if(vno==4){
    if(tview==0){
    eye=glm::vec3 ( player.position.x-15, player.position.y+10, player.position.z+15 );
    tview=1;
    }
    target=glm::vec3 ( player.position.x, 0, player.position.z );
    up=glm::vec3 (0, 1,0);
}

if(vno==5){
glfwGetCursorPos(window, &mousex, &mousey);
        ax = 180*(300-mousey)/600;
        ay = 180*(300-mousex)/600;
        if(ax<=-90)ax=-89;
        if(ay<=-90)ay=-89;
        if(ax>=90)ax=89;
        if(ay>=90)ay=89;
        eye    = glm::vec3(player.position.x - radius * sin(glm::radians(ay-player.rotationy)), player.position.y + radius * sin(glm::radians(ax)), player.position.z + radius * cos(glm::radians(ay-player.rotationy))*cos(glm::radians(ax)));
        target = glm::vec3(player.position.x, player.position.y+2, player.position.z-3);
        up     = glm::vec3(0,1,0);
}
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);


     // Compute Camera matrix (view)
     changeveiw();
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    M1.view = glm::lookAt( eye1, tar1, up1 ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP1 = M1.projection * M1.view;


    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    // wall.draw(VP);
    plat.draw(VP);
    player.draw(VP);
    // p1.draw(VP);
    for(int i=0;i<grounds.size();i++){
    grounds[i].draw(VP);
    }
    for(int i=0;i<volcanos.size();i++){
    volcanos[i].draw(VP);
    }
    for(int i=0;i<smokes.size();i++){
    smokes[i].draw(VP);
    }
    for(int i=0;i<fuel.size();i++){
    fuel[i].draw(VP);
    }
    arrow.draw(VP,player.position.x,player.position.y,player.position.z);
    for(int i=0;i<enemies.size();i++){
    enemies[i].draw(VP);
    }
    for(int i=0;i<cannons.size();i++){
    cannons[i].draw(VP);
    }
    for(int i=0;i<msize;i++){
        if(missiles[i].render==1)
    missiles[i].draw(VP);
    }
    for(int i=0;i<bombs1.size();i++){
    bombs1[i].draw(VP);
    }
    for(int i=0;i<explosions.size();i++){
        // cout<<"kmt";
    explosions[i].draw(VP);
    }
    for(int i=0;i<bsize;i++){
        if(bombs[i].render==1)
    bombs[i].draw(VP);
    }
    for(int i=0;i<health.size();i++){
        health[i].draw(VP);
    }
    bar.position.x=4.5;
    bar.position.y=5;
    bar.position.z=0;
    bar.draw(VP1);
    altitude.position.x=5;
    altitude.position.y=5;
    altitude.position.z=0;
    altitude.draw(VP1);
    compass.draw(VP1);
}

void shoot(){
    float x=player.rotationx*M_PI/180.0f;
    float y=player.rotationy*M_PI/180.0f;
    float z=player.rotationz*M_PI/180.0f;
    Missile m=Missile(player.position.x,player.position.y,player.position.z,0.1*sin(y)*sin(x),0.1*cos(x),0.1*cos(y)*sin(x),player.rotationx,player.rotationy,player.rotationz,COLOR_BLACK);
    missiles[msize++]=m;
}
void shoot1(){
    float x=player.rotationx*M_PI/180.0f;
    float y=player.rotationy*M_PI/180.0f;
    float z=player.rotationz*M_PI/180.0f;
    Bomb b=Bomb(player.position.x,player.position.y,player.position.z,0,-0.1,0,COLOR_BLACK);
    bombs[bsize++]=b;
}

void barell(){
    roll=1;
    cx=player.position.x+2;
    cy=player.position.y;
}

void collision(){
    
    for(int i=0;i<smokes.size();i++){
        float x_diff=smokes[i].position.x-player.position.x;
        float y_diff=smokes[i].position.y-player.position.y;
        float z_diff=smokes[i].position.z-player.position.z;
        float dist=pow(pow(x_diff,2)+pow(y_diff,2),0.5);
        if(dist<=2 && abs(z_diff)<0.1) bar.reading=0;     
    }

    for(int i=0;i<volcanos.size();i++){
        float x_diff=volcanos[i].position.x-player.position.x;
        float y_diff=volcanos[i].position.y-player.position.y;
        float z_diff=volcanos[i].position.z-player.position.z;
        float dist=pow(pow(x_diff,2)+pow(z_diff,2),0.5);
        if(dist<=7 && abs(y_diff)<volcanos[i].height+3){
            h-=0.01;
            if(h<0)
             quit(window);
        }
    }

    for(int i=0;i<fuel.size();i++){
        float x=player.rotationx*M_PI/180.0f;
    float y=player.rotationy*M_PI/180.0f;
    float z=player.rotationz*M_PI/180.0f;
        float x_diff=fuel[i].position.x-player.position.x-2*sin(y)*sin(x);
        float y_diff=fuel[i].position.y-player.position.y-2*cos(x);
        float z_diff=player.position.z-fuel[i].position.z;
        if(z_diff<=abs(2*cos(y)*sin(x))){
            float dist=pow(pow(x_diff,2)+pow(y_diff,2),0.5);
            if(dist<=1.7){
             fuel.erase(fuel.begin()+i);
             bar.reading=0;
            }
        } 
    }


    for(int i=0;i<health.size();i++){
         bounding_box_t* a=new bounding_box_t(player.position.x,player.position.y,player.position.z+1,2,2,6);
         bounding_box_t* b=new bounding_box_t(health[i].position.x,health[i].position.y,health[i].position.z,1,1,1);
        if(detect_collision(a,b)){
            h+=4;
            if(h>10) h=10;
            health.erase(health.begin()+i);
        }
    }


    for(int i=0;i<bombs1.size();i++){
         bounding_box_t* a=new bounding_box_t(player.position.x,player.position.y,player.position.z+1,2,2,6);
         bounding_box_t* b=new bounding_box_t(bombs1[i].position.x,bombs1[i].position.y,bombs1[i].position.z,0.25,0.25,0.25);
        if(detect_collision(a,b)){
            h-=0.05;
            if(h<=0)
            quit(window);
        // cout<<i<<endl<<player.position.x<<" "<<player.position.y<<" "<<player.position.z<<" "<<bombs1[i].position.x<<" "<<bombs1[i].position.y<<" "<<bombs1[i].position.z<<endl;
        // cout<<a->x<<" "<<a->y<<" "<<a->z<<" "<<b->x<<" "<<b->y<<" "<<b->z<<endl;        
        }
    }
    for(int i=0;i<msize;i++){
        float mx=missiles[i].position.x;
        float my=missiles[i].position.y;
        float mz=missiles[i].position.z;
        for(int j=0;j<cannons.size();j++){
            float cx=cannons[j].position.x;
            float cy=cannons[j].position.y;
            float cz=cannons[j].position.z;
            bounding_box_t* a=new bounding_box_t(cx,cy,cz,1,1,1);
            bounding_box_t* b=new bounding_box_t(mx,my,mz-0.375,0.25,0.25,1.75);
            if(detect_collision(a,b)) {
                cout<<i<<endl;
                cannons.erase(cannons.begin()+j);
                finish=1;
            }
        }
        for(int j=0;j<enemies.size();j++){
            float ex=enemies[j].position.x;
            float ey=enemies[j].position.y;
            float ez=enemies[j].position.z;
            // bounding_box_t* a=new bounding_box_t(ex,ey+1.5,ez,2,1,0);
            bounding_box_t* b=new bounding_box_t(mx,my,mz-0.375,0.25,0.25,1.75);
            bounding_box_t* c=new bounding_box_t(ex,ey,ez,2,2,0.0);
            if(detect_collision(b,c)) {
                cout<<i<<endl;
                enemies.erase(enemies.begin()+j);
                score+=10;
            }
        }
    }

    for(int i=0;i<bsize;i++){
        float bx=bombs[i].position.x;
        float by=bombs[i].position.y;
        float bz=bombs[i].position.z;
        for(int j=0;j<grounds.size();j++){
            float gx=grounds[j].position.x;
            float gy=grounds[j].position.y;
            float gz=grounds[j].position.z;
            if(by-gy<=0.125){
                    float dist=pow(pow(gx-bx,2)+pow(gz-bz,2),0.5);
                    if(dist<=grounds[j].radius){
                        Explosion e=Explosion(gx,gy,gz,grounds[j].radius*2,COLOR_BLACK);
                        explosions.push_back(e);
                         grounds.erase(grounds.begin()+j);
                         cannons.erase(cannons.begin()+j);
                        finish=1;
                    }
            }
            
        }
    }
}
void tick_input(GLFWwindow *window) {
    int d  = glfwGetKey(window, GLFW_KEY_D);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int up    = glfwGetKey(window,GLFW_KEY_UP);
    int down    = glfwGetKey(window,GLFW_KEY_DOWN);
    int right    = glfwGetKey(window,GLFW_KEY_RIGHT);
    int left    = glfwGetKey(window,GLFW_KEY_LEFT);
    int z    = glfwGetKey(window,GLFW_KEY_Z);
    int y    = glfwGetKey(window,GLFW_KEY_Y);
    int y1    = glfwGetKey(window,GLFW_KEY_E);
    int x    = glfwGetKey(window,GLFW_KEY_X);
    int m    = glfwGetKey(window,GLFW_KEY_M);
    int plane_view=glfwGetKey(window,GLFW_KEY_1);
    int top_view=glfwGetKey(window,GLFW_KEY_2);
    int follow_view=glfwGetKey(window,GLFW_KEY_3);
    int normal_view=glfwGetKey(window,GLFW_KEY_0);
    int tower_view=glfwGetKey(window,GLFW_KEY_4);
    int heli_view=glfwGetKey(window,GLFW_KEY_5);
// glfwGetCursorPos(window, &mousex, &mousey);
if(heli_view) vno=5;
if(tower_view) vno=4;
if(plane_view) vno=1;
if(top_view) vno=2;
if(follow_view) vno=3;
if(normal_view) vno=0;

if(z){
    player.rotationz+=1;
    bar.tick(0.005);
    // p1.rotationz+=1;
}

if(y){
    player.rotationy+=1;
    bar.tick(0.005);
}


if(y1){
    player.rotationy-=1;
    bar.tick(0.005);
}

if(x){
    player.rotationx+=1;
    bar.tick(0.005);

}

if(space){
player.position.y+=0.2;
    bar.tick(0.001);

}
if(d){
    player.position.y-=0.2;
    bar.tick(0.002);

}
if(down){
    player.position.z+=0.5*cos(player.rotationy*M_PI/180.0f);
player.position.x+=0.5*sin(player.rotationy*M_PI/180.0f);
    bar.tick(0.003);

}
if(up){
player.position.z-=0.5*cos(player.rotationy*M_PI/180.0f);
player.position.x-=0.5*sin(player.rotationy*M_PI/180.0f);
    bar.tick(0.003);

}
if(right){
    player.position.x+=0.5;
    bar.tick(0.005);
}
if(left){
    player.position.x-=0.5;
    bar.tick(0.005);
}
}

void tick_elements() {
    if(bar.reading==1.5 || altitude.reading==1.5 || player.position.y==-0.1) quit(window);
        if(bangle<2*3.14 && roll==1){
            // player.vz+=0.02;
            player.position.x=cx+2*cos(bangle);
            player.position.y=cy+2*sin(bangle);
            cout<<player.position.x<<endl;
            bangle+=0.03;
        }
        if(bangle>=2*3.14 && roll==1) roll=0;
    bar.tick(0.0001);
    player.tick();
    arrow.tick();
    for(int i=0;i<health.size();i++) health[i].tick();
    for(int i=0;i<enemies.size();i++) enemies[i].tick();
    altitude.tick1((-(player.position.y+1)*1.5/20)+1.5);
    float x_diff=checkpoints[ccount].x-player.position.x;
    float z_diff=checkpoints[ccount].z-player.position.z;
    compass.rotationz=atan(x_diff/z_diff)*180/M_PI;
    // compass.rotationy=
    for(int i=0;i<msize;i++){
    missiles[i].tick();
    }
    for(int i=0;i<bsize;i++){
    bombs[i].tick();
    }
    for(int i=0;i<bombs1.size();i++){
    bombs1[i].tick();
    }
    for(int i=0;i<cannons.size();i++){
        Cannon c =cannons[i];
        float x_diff=c.position.x-player.position.x;
        float y_diff=c.position.y-player.position.y;
        float z_diff=c.position.z-player.position.z; 
        float dist=pow(pow(x_diff,2)+pow(z_diff,2),0.5);
        if(dist<8.414){
            if (clock()-c.count>=CLOCKS_PER_SEC){
                Bomb b=Bomb(c.position.x,c.position.y,c.position.z,-0.01*x_diff,-0.01*y_diff,-0.01*z_diff,COLOR_BLACK);
                bombs1.push_back(b);
                cannons[i].count=clock();
            }
        }
    }
    if(abs(player.position.z-checkpoints[ccount].z)<0.5 && finish==1){
        ccount++;       
       arrow.position.x=checkpoints[ccount].x;
       arrow.position.y=checkpoints[ccount].y; 
       arrow.position.z=checkpoints[ccount].z;
       finish=0; 
        }
    collision();
    // reset_screen();
    score+=(clock()-initime)/CLOCKS_PER_SEC;
    initime=clock();
    sprintf(title,"Score: %f Health: %f",round(score),h);
    glfwSetWindowTitle(window,title);
    reset_screen();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    player       =Plane(0, 0,15, COLOR_BLACK,0,0);
    checkpoints[0].x=player.position.x;
    p1       =Plane(0, 4,-30, COLOR_BLACK,0,0);
    wall         =Wall(0,0,COLOR_GREEN);
    plat         =Platform(0,0,COLOR_ORANGE);
     Fuel fuel1         =Fuel(0,2,0,COLOR_GREEN);
     fuel.push_back(fuel1);
     for(int i=1;i<100;i++){
         float r =15-30*double(rand()) / (double(RAND_MAX) + 1.0);
         float r1 =8+8*double(rand()) / (double(RAND_MAX) + 1.0);
         float h =2+4*double(rand()) / (double(RAND_MAX) + 1.0);
        fuel1=Fuel(fuel[i].position.x+r,h,fuel[i-1].position.z-r1,COLOR_GREEN);
        fuel.push_back(fuel1);
     }

     for(int i=0;i<6;i++){
    Ground g        =Ground(checkpoints[i].x,-1.9,checkpoints[i].z,4,COLOR_LGREEN);
    grounds.push_back(g);
    Cannon c          =Cannon(checkpoints[i].x,grounds[i].position.y,checkpoints[i].z,0,0,0,COLOR_DGREEN);
    cannons.push_back(c);
        cannons[i].count=clock();
        Health h          =Health(checkpoints[i].x+4,grounds[i].position.y+3,checkpoints[i].z,0,0,0,COLOR_WHITE);
        health.push_back(h);
     }



    Volcano v        =Volcano(0,-1.9,0,3,COLOR_BROWN);
    volcanos.push_back(v);
     for(int i=1;i<40;i++){
         float r =30-80*double(rand()) / (double(RAND_MAX) + 1.0);
         float r1 =33+5*double(rand()) / (double(RAND_MAX) + 1.0);
         float h =4+6*double(rand()) / (double(RAND_MAX) + 1.0);
        v=Volcano(r,-1.9,volcanos[i-1].position.z-r1,h,COLOR_BROWN);
        volcanos.push_back(v);
     }




    arrow           =Arrow(checkpoints[ccount].x,checkpoints[ccount].y+8,checkpoints[ccount].z,COLOR_BRED,0);
    compass           =Compass(-1,6,0,COLOR_BLACK);    
    bar           =Bar(-2,6,-5,COLOR_RED,COLOR_YELLOW,COLOR_GREEN,COLOR_BLACK);
    altitude           =Bar(-2,6,-5,COLOR_RED,COLOR_GREEN,COLOR_GREEN,COLOR_BLACK);
    Enemy e           =Enemy(3,6,-5,COLOR_MAGENTA);
    enemies.push_back(e);
    for(int i=1;i<40;i++){
         float r =30-80*double(rand()) / (double(RAND_MAX) + 1.0);
         float r1 =30+5*double(rand()) / (double(RAND_MAX) + 1.0);
         float h =6+4*double(rand()) / (double(RAND_MAX) + 1.0);
        e=Enemy(r,h,enemies[i-1].position.z-r1,COLOR_BLACK);
        enemies.push_back(e);
     }
    Smoke s           =Smoke(0,5,-10,COLOR_BLACK);
    smokes.push_back(s);
    for(int i=1;i<40;i++){
         float r =10-20*double(rand()) / (double(RAND_MAX) + 1.0);
         float r1 =60+5*double(rand()) / (double(RAND_MAX) + 1.0);
         float h =5+6*double(rand()) / (double(RAND_MAX) + 1.0);
        s=Smoke(smokes[i-1].position.x+r,h,smokes[i-1].position.z-r1,COLOR_BLACK);
        smokes.push_back(s);
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
initime=clock();
    window = initGLFW(width, height);
for(int i=0;i<100;i++){
    checkpoints[i].x=2;
    checkpoints[i].y=3;
    checkpoints[i].z=-150*i-20;
}
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
            tick_input(window);
            tick_elements();

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t* a, bounding_box_t* b) {
    return (abs(a->x - b->x) * 2 < (a->length + b->length)) &&
           (abs(a->y - b->y) * 2 < (a->width + b->width)) && 
           (abs(a->z - b->z) * 2 < (a->height + b->height));           ;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    M1.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
