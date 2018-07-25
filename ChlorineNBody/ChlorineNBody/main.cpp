//
//  main.cpp
//  ChlorineNBody
//
//  Created by Jack Armstrong on 7/24/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <stdlib.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include "chlorine.hpp"
#include <vector>

typedef std::vector<float> flist;
typedef std::vector<int> blist;

flist x;
flist y;
flist z;
flist vx;
flist vy;
flist vz;
flist mass;
blist isTracer;

const int num_particles=10000;
const float dt=0.01f;
const float G=0.01f;

float rand(float mi,float ma){return mi + (float) rand() /( static_cast <float> (RAND_MAX/(ma-mi)));}

ch::Worker kernel;
cl::Event event;

const float NANO_IN_SECOND=1000000000.0f;
float updateTime;
void init(){
    kernel=ch::Worker("nbody.cl");
    
    for(int i=0;i<num_particles;i++){
        float ang=rand(0,6.2831853072);
        float r=rand(0,20);
        x.push_back(r*cos(ang));
        y.push_back(r*sin(ang));
//        z.push_back(rand(-10,10));
        z.push_back(0);
        vx.push_back(0);
        vy.push_back(0);
        vz.push_back(0);
        bool tracer=rand(0,1)<0.1;
        if(tracer){
            mass.push_back(10);
            isTracer.push_back(true);
        }else{
            mass.push_back(rand(0,1)<0.9?10:100);
            isTracer.push_back(false);
        }
//        mass.push_back(1);
    }
}

void display(){
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    glEnable(GL_ALPHA_BITS);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glEnable(GL_POINT_SMOOTH);
    glOrtho(-50, 50, -50, 50, -100, 100);
    glPointSize(3);
//    glColor4f(0.2, 0.6, 1.0, 1.0);
    glBegin(GL_POINTS);
    for(int i=0;i<num_particles;i++){
        if(mass[i]<50)glColor4f(0, 0, 0, 1);
        else glColor4f(0.5, 0.5, 0.5, 1);
        if(isTracer[i])glColor4f(0, 0, 0, 0.1);
        glVertex3f(x[i],y[i],z[i]);
    }
    glEnd();
    
    glutSwapBuffers();
}
//seperate x,y
//no clever interleaving

void update(){
    updateTime=0.0f;
    event=kernel.call("nbody", x,y,z,vx,vy,vz,isTracer,mass,num_particles,dt,G);
    updateTime+=ch::elapsed(event);
//    printf("Time: %f\n",updateTime/NANO_IN_SECOND);
    
    glutPostRedisplay();
}

int main(int argc, char * argv[]) {
    srand(time(NULL));
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 300);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutCreateWindow("Chlorine / OpenCL / N-Body Simulation");
    
    init();
    
    glutDisplayFunc(display);
    glutIdleFunc(update);
    
    glutMainLoop();
    return 0;
}
