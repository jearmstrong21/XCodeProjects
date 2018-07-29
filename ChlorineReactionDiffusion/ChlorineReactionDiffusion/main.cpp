//
//  main.cpp
//  ChlorineReactionDiffusion
//
//  Created by Jack Armstrong on 7/26/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <stdlib.h>
#include <OpenGL/gl.h>
#include "chlorine.hpp"
#include <GLUT/glut.h>
#include <vector>

typedef std::vector<float> flist;

const int SIMSIZE=500;

//global float*gridA,global float*gridB,float Da,float Db,float f,float k,float dt

flist gridA;
flist gridB;
float paramK;
float paramF;
float paramDa;
float paramDb;
float paramDt;

int ind(int x,int y){
    return x+y*SIMSIZE;
}

ch::Worker kernel;

void mouse(int button,int state,int x,int y){
    
}

void init(){
    kernel=ch::Worker("reactiondiffusion.cl");
//    gridA=(float*)malloc(sizeof(float)*SIMSIZE*SIMSIZE);
//    gridB=(float*)malloc(sizeof(float)*SIMSIZE*SIMSIZE);
    for(int i=0;i<SIMSIZE*SIMSIZE;i++){
        gridA.push_back(1);
        int x=i/SIMSIZE;
        int y=i%SIMSIZE;
        if(x>SIMSIZE/2-10&&x<SIMSIZE/2+10)gridB.push_back(1);
        else gridB.push_back(0);
    }
    paramDa=1.0;
    paramDb=0.5;
    paramF=0.0367;
    paramK=0.0649;
    paramDt=1.0;
}

int frames=0;

void update(){
    frames++;
    if(frames%1==0)
    cl::Event evt=kernel.call("reactiondiffusion",gridA,gridB,paramDa,paramDb,paramF,paramK,paramDt,SIMSIZE);
    //why is it fading?
    glutPostRedisplay();
}

void render(){
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    glOrtho(0, SIMSIZE, 0, SIMSIZE, 0, 1);
    
    glBegin(GL_QUADS);
    for(int x=0;x<SIMSIZE;x++){
        for(int y=0;y<SIMSIZE;y++){
            float a=gridA[ind(x,y)];
            float b=gridB[ind(x,y)];
            glColor3f(a,b,0);
            glVertex3f(x,y,0);
            glVertex3f(x+1,y,0);
            glVertex3f(x+1,y+1,0);
            glVertex3f(x,y+1,0);
        }
    }
    glEnd();
    
    glutSwapBuffers();
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(SIMSIZE, SIMSIZE);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_ALPHA | GLUT_DOUBLE);
    glutCreateWindow("Chlorine / OpenCL / SPH Simulation");
    
    init();
    
    glutMouseFunc(mouse);
    glutDisplayFunc(render);
    glutIdleFunc(update);
    
    glutMainLoop();
    return 0;
}
