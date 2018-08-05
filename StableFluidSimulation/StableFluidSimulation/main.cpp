//
//  main.cpp
//  StableFluidSimulation
//
//  Created by Jack Armstrong on 8/3/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>

#include <cmath>

#include "Grid.hpp"
#include "Update.hpp"
#include "HSB.hpp"

#include <vector>

Grid vx;
Grid vy;
Grid density;
Grid pressure;
Grid divergence;

struct particle{
    float x;
    float y;
};

float rand(float a,float b){
    int i=rand();
    i=i%10000;
    float f=((float)i)/10000.0;
    return f*(b-a)+a;
}

typedef std::vector<particle> plist; // plist is a particle list

plist particles;

const int DIVERGENCE=0;
const int VEL=1;
const int DENS=2;
const int PRES=3;
const int DENS_VEL_OVERLAY=4;
const int NONE=-1;

const bool DENS_HSB=false;

const bool VEL_OVERLAY_HSB=true;
const int VEL_OVERLAY_SPACING=4;
const float VEL_OVERLAY_MULT=8;

const bool VEL_HSB=true;

const bool PRES_HSB=true;

const bool DIVERG_HSB=true;

int drawMode=DENS_VEL_OVERLAY;

#define WINDOW_SCALE 5
float sq(float f){
    return f*f;
}
int lastX=0;
int lastY=0;

bool mousePressed=false;
bool leftBtn=false;

void keyPress(unsigned char key,int x,int y){
    if(key=='1')drawMode=DENS;
    else if(key=='2')drawMode=DENS_VEL_OVERLAY;
    else if(key=='3')drawMode=VEL;
    else if(key=='4')drawMode=PRES;
    else if(key=='5')drawMode=DIVERGENCE;
    
    
    
    else if(key=='0')drawMode=NONE;
}

void mousePress(int btn,int state,int x,int y){
    
    x/=WINDOW_SCALE;
    y/=WINDOW_SCALE;
    
    if(btn==GLUT_LEFT_BUTTON)leftBtn=true;
    else leftBtn=false;
    if(state==GLUT_UP)mousePressed=false;
    else mousePressed=true;
}

void passiveMouseMove(int x,int y){
    x/=WINDOW_SCALE;
    y/=WINDOW_SCALE;
    y=GRIDSIZE-y;
    
//    for(int i=0;i<GRIDSIZE;i++){
//        for(int j=0;j<GRIDSIZE;j++){
//            if(sqrt(sq(x-i)+sq(y-j))<20){
//                density.data[i][j]+=0.1;
//            }
//        }
//   }
    float dx=x-lastX;
    float dy=y-lastY;
    float mult=0.1;
    for(int i=0;i<GRIDSIZE;i++){
        for(int j=0;j<GRIDSIZE;j++){
            
            if(sqrt(sq(x-i)+sq(y-j))<20){
                vx.data[i][j]+=mult*dx;
                vy.data[i][j]+=mult*dy;
            }
            
        }
    }
    
    lastX=x;
    lastY=y;
}

void idle(){
    update(vx, vy, density, pressure, divergence);
    
    if(mousePressed){
        for(int x=0;x<GRIDSIZE;x++){
            for(int y=0;y<GRIDSIZE;y++){
                if(sqrt(sq(x-lastX)+sq(y-lastY))<20){
                    density.data[x][y]+=0.05*(leftBtn?-1:1);
                }
            }
        }
    }
    
    float m=3;
    for(int i=0;i<particles.size();i++){
        particle &p=particles[i];
        p.x+=vx(p.x,p.y);
        p.y+=vy(p.x,p.y);
//        if(p.x<m||p.y<m||p.x>=GRIDSIZE-m||p.y>=GRIDSIZE-m){
//            p.x=rand(0,GRIDSIZE);
//            p.y=rand(0,GRIDSIZE);
//        }
        while(p.x<0)p.x+=GRIDSIZE;
        while(p.y<0)p.y+=GRIDSIZE;
        while(p.x>=GRIDSIZE)p.x-=GRIDSIZE;
        while(p.y>=GRIDSIZE)p.y-=GRIDSIZE;
    }
    
    glutPostRedisplay();
}

void displayDens(){
    glBegin(GL_QUADS);
    for(int x=0;x<GRIDSIZE;x++){
        for(int y=0;y<GRIDSIZE;y++){
            float f=density(x,y);
            if(DENS_HSB)glColor3f(thetaToR(f),thetaToG(f),thetaToB(f));
            else glColor3f(fmod(f, 1),fmod(f,1),fmod(f,1));
            glVertex2f(x,y);
            glVertex2f(x+1,y);
            glVertex2f(x+1,y+1);
            glVertex2f(x,y+1);
        }
    }
    glEnd();
}

void displayVelOverlay(){
    glBegin(GL_LINES);
    for(int x=0;x<GRIDSIZE;x+=VEL_OVERLAY_SPACING){
        for(int y=0;y<GRIDSIZE;y+=VEL_OVERLAY_SPACING){
            float velMag=sqrt(sq(vx(x,y))+sq(vy(x,y)));
            if(VEL_OVERLAY_HSB)glColor3f(thetaToR(velMag), thetaToG(velMag), thetaToB(velMag));
            else glColor3f(fmod(velMag,1),fmod(velMag,1),fmod(velMag,1));
            glVertex2f(x+WINDOW_SCALE/2, y+WINDOW_SCALE/2);
            glVertex2f(x+WINDOW_SCALE/2+vx(x,y)*VEL_OVERLAY_MULT, y+WINDOW_SCALE/2+vy(x,y)*VEL_OVERLAY_MULT);
        }
    }
    glEnd();
}

void displayVel(){
    glBegin(GL_QUADS);
    for(int x=0;x<GRIDSIZE;x++){
        for(int y=0;y<GRIDSIZE;y++){
            float velMag=sqrt(sq(vx(x,y))+sq(vy(x,y)));
            if(VEL_HSB)glColor3f(thetaToR(velMag), thetaToG(velMag), thetaToB(velMag));
            else glColor3f(fmod(velMag,1),fmod(velMag,1),fmod(velMag,1));
            glVertex2f(x, y);
            glVertex2f(x+1,y);
            glVertex2f(x+1,y+1);
            glVertex2f(x,y+1);
        }
    }
    glEnd();
}

void displayPres(){
    glBegin(GL_QUADS);
    for(int x=0;x<GRIDSIZE;x++){
        for(int y=0;y<GRIDSIZE;y++){
            float f=pressure(x,y);
            if(PRES_HSB)glColor3f(thetaToR(f),thetaToG(f),thetaToB(f));
            else glColor3f(fmod(f, 1),fmod(f,1),fmod(f,1));
            glVertex2f(x,y);
            glVertex2f(x+1,y);
            glVertex2f(x+1,y+1);
            glVertex2f(x,y+1);
        }
    }
    glEnd();
}

void displayDivergence(){
    glBegin(GL_QUADS);
    for(int x=0;x<GRIDSIZE;x++){
        for(int y=0;y<GRIDSIZE;y++){
            float f=divergence(x,y);
            if(DIVERG_HSB)glColor3f(thetaToR(f),thetaToG(f),thetaToB(f));
            else glColor3f(fmod(f, 1),fmod(f,1),fmod(f,1));
            glVertex2f(x,y);
            glVertex2f(x+1,y);
            glVertex2f(x+1,y+1);
            glVertex2f(x,y+1);
        }
    }
    glEnd();
}

void displayParticles(){
    glPointSize(2);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    for(int i=0;i<particles.size();i++){
        particle &p=particles[i];
        float d=density(p.x,p.y);
        glColor3f(1*d,0,0);
        glVertex2f(p.x, p.y);
    }
    glEnd();
}

void display(){
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLoadIdentity();
    
    glOrtho(0, GRIDSIZE, 0, GRIDSIZE, 0, 1);
    
    if(drawMode==DENS){
        displayDens();
    }
    if(drawMode==DENS_VEL_OVERLAY){
        displayDens();
        displayVelOverlay();
    }
    if(drawMode==VEL){
        displayVel();
    }
    if(drawMode==PRES){
        displayPres();
    }
    if(drawMode==DIVERGENCE){
        displayDivergence();
    }
    
    displayParticles();
    
    glutSwapBuffers();
}


int main(int argc,char*argv[]){
    glutInit(&argc, argv);
    
    vx.init();
    vy.init();
    density.init();
    pressure.init();
    divergence.init();
    
    for(int i=0;i<200*1000;i++){//fix vel on corners AND dens on corners
        particle p;
        p.x=rand(0,GRIDSIZE);
        p.y=rand(0,GRIDSIZE);
        particles.push_back(p);
    }
    
    
    int spacing=20;
    float TWO_PI=6.2831853072;
    for(int x=0;x<GRIDSIZE;x++){
        for(int y=0;y<GRIDSIZE;y++){
            float fx=(1.0*x)/GRIDSIZE;
            float fy=(1.0*y)/GRIDSIZE;
            vx.set(x,y, cos(fy*TWO_PI));
            vy.set(x,y, sin(fx*TWO_PI));
//            vx.set(x,y,  fx-0.5);
//            vy.set(x,y,  fy-0.5);
//            vx.set(x,y,  1);
//            vy.set(x,y,  sin(TWO_PI*fx));
            pressure.set(x,y,  0);
            density.set(x,y,  0);
            divergence.set(x,y,  0);
            if(  (x/spacing)%2+(y/spacing)%2==1)density.set(x,y, 1);
//            if(sqrt( (x-GRIDSIZE/2)*(x-GRIDSIZE/2) + (y-GRIDSIZE/2)*(y-GRIDSIZE/2)  )<10){
//                density.set(x,y,  10);
//            }
        }
    }
    
    glutInitWindowSize(GRIDSIZE*WINDOW_SCALE, GRIDSIZE*WINDOW_SCALE);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Stable fluid simulation");
    
    glutPassiveMotionFunc(passiveMouseMove);
    glutKeyboardFunc(keyPress);
    
    glutMouseFunc(mousePress);
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    
    glutMainLoop();
}
