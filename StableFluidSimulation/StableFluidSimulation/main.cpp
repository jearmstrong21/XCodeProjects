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

Grid vx;
Grid vy;
Grid density;
Grid pressure;
Grid divergence;

#define WINDOW_SCALE 5
float sq(float f){
    return f*f;
}
int lastX=0;
int lastY=0;

bool mousePressed=false;
bool leftBtn=false;

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
    
    glutPostRedisplay();
}

void display(){
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLoadIdentity();
    
    glOrtho(0, GRIDSIZE, 0, GRIDSIZE, 0, 1);
    
    
    glBegin(GL_QUADS);
    for(int x=0;x<GRIDSIZE;x++){
        for(int y=0;y<GRIDSIZE;y++){
            float f=density(x,y);
            glColor3f(f,f,f);
            glVertex2f(x,y);
            glVertex2f(x+1,y);
            glVertex2f(x+1,y+1);
            glVertex2f(x,y+1);
        }
    }
    glEnd();
    
//    int spacing=10;
//    float mag=7;
//    glBegin(GL_LINES);
//    for(int x=0;x<GRIDSIZE;x+=spacing){
//        for(int y=0;y<GRIDSIZE;y+=spacing){
//            float f=density(x,y);
//            glColor3f(1-f,1-f,1-f);
//            glVertex2f(x, y);
//            glVertex2f(x+mag*vx(x,y),y+mag*vy(x,y));
//        }
//    }
//    glEnd();
    
    glutSwapBuffers();
}

int main(int argc,char*argv[]){
    glutInit(&argc, argv);
    
    vx.init();
    vy.init();
    density.init();
    pressure.init();
    divergence.init();
    
    
    int spacing=5;
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
    
    glutMouseFunc(mousePress);
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    
    glutMainLoop();
}
