//
//  main.cpp
//  ChlorineSPH
//
//  Created by Jack Armstrong on 7/25/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <stdlib.h>
#include <cmath>
#include <vector>

#include "chlorine.hpp"
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

typedef std::vector<float> flist;
typedef std::vector<int> ilist;

flist listx;
flist listy;
ilist listgx;
ilist listgy;
flist listvx;
flist listvy;
flist listfx;
flist listfy;
flist listrho;
flist listp;

const int SIM_WIDTH=1000;
const int SIM_HEIGHT=1000;

int num_particles=1000;

const float G_x=0;
const float G_y=12000*-9.8;
const float REST_DENS=1000;
const float GAS_CONST=2000;
const float H=25;
const float HSQ=H*H;
const float MASS=65;
const float VISC=1500;
const float DT=0.0002;

const float PI=3.1415926536;

const float POLY6=315/(65*PI*pow(H,9));
const float SPIKY_GRAD=-45/(PI*pow(H,6));
const float VISC_LAP=45/(PI*pow(H,6));

const float BOUND_SIZE=40;
const float BOUND_DAMPING=-0.5;

const float DISPLAY_SIZE=H;


const float NANO_IN_SECOND=1000000000.0f;

float rand(float mi,float ma){return mi + (float) rand() /( static_cast <float> (RAND_MAX/(ma-mi)));}

void addParticle(float x,float y){
    listgx.push_back(0);
    listgy.push_back(0);
    listx.push_back(x);
    listy.push_back(y);
    listvx.push_back(0);
    listvy.push_back(0);
    listfx.push_back(0);
    listfy.push_back(0);
    listrho.push_back(0);
    listp.push_back(0);
    //for ChlorineSPHGridded, calculate gridX,gridY and then check box radius inside loops
}

ch::Worker kernel;
cl::Event event;
float clTime;

void init(){
    for(int i=0;i<num_particles;i++){
//        addParticle(rand(0,SIM_WIDTH), rand(0,SIM_HEIGHT));
        addParticle(SIM_WIDTH/2+rand(-50,50), SIM_HEIGHT/2+rand(-50,50));
    }
    kernel=ch::Worker("gridded-sph.cl");
}

cl::Event callKernel(const std::string name){
    return kernel.call(name,listgx,listgy,listx,listy,listvx,listvy,listfx,listfy,listrho,listp,G_x,G_y,REST_DENS,GAS_CONST,H,HSQ,MASS,VISC,DT,POLY6,SPIKY_GRAD,VISC_LAP,BOUND_SIZE,BOUND_DAMPING,(float)SIM_WIDTH,(float)SIM_HEIGHT,num_particles);
}

void mouse(int button,int state,int x,int y){
    addParticle(x, y);
    printf("mouse: %i,%i\n",x,y);
}

void update(){
    for(int i=0;i<1;i++){
        event=callKernel("ComputeGridPositions");
        event=callKernel("ComputeDensityPressure");
        event=callKernel("ComputeForces");
        event=callKernel("Integrate");
    }
    
    
    glutPostRedisplay();
}

void render(){
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
//    glEnable(GL_ALPHA_BITS);
//    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glEnable(GL_POINT_SMOOTH);
    glOrtho(0, SIM_WIDTH, 0, SIM_HEIGHT, 0, 1);
    glPointSize(DISPLAY_SIZE);
    glColor4f(0.2, 0.6, 1.0, 1.0);
    glBegin(GL_POINTS);
    for(int i=0;i<num_particles;i++){
        glVertex3f(listx[i],listy[i],0);
//        glVertex3f(listgx[i]*SIM_WIDTH/H/2,listgy[i]*SIM_HEIGHT/H/2,0);
    }
    glEnd();
    
    glutSwapBuffers();
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitWindowSize(SIM_WIDTH, SIM_HEIGHT);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_ALPHA | GLUT_DOUBLE);
    glutCreateWindow("Chlorine / OpenCL / SPH Simulation");
    
    init();
    
    glutMouseFunc(mouse);
    glutDisplayFunc(render);
    glutIdleFunc(update);
    
    glutMainLoop();
}
