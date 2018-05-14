//
//  main.cpp
//  HelloXCode
//
//  Created by Jack Armstrong on 5/4/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include "glm/mat4x4.hpp"

int windowWidth=1000;
int windowHeight=1000;
int f=0;
int mouseX=0,mouseY=0;
void vertex(float a,float b,float c){
    glColor3f(a+0.5,b+0.5,c+0.5);
//    float f=4;
    glVertex3f(a,b,c);
}
void render_scene(){
    f+=2;
    
    std::cout<<"Render start"<<std::endl;
    windowWidth=glutGet(GLUT_WINDOW_WIDTH);
    windowHeight=glutGet(GLUT_WINDOW_HEIGHT);
    std::cout<<windowWidth<<" "<<windowHeight<<std::endl;
    float ratio = windowWidth / (float) windowHeight;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DITHER);
    glDepthFunc(GL_LESS);
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.25, 0.25, 0.25, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    gluPerspective(180, 1.0*windowHeight/windowWidth, 0, 1);
    glLoadIdentity();
    glRotatef(-40,1,0,0);
    glRotatef(f,0,1,0);
    float a=0.25;
    glBegin(GL_POLYGON);
    vertex(-a,a,a);
    vertex(-a,-a,a);
    vertex(-a,-a,-a);
    vertex(-a,a,-a);
    glEnd();
    glBegin(GL_POLYGON);
    vertex(a,a,a);
    vertex(a,-a,a);
    vertex(a,-a,-a);
    vertex(a,a,-a);
    glEnd();
    glBegin(GL_POLYGON);
    vertex(a,-a,a);
    vertex(a,-a,-a);
    vertex(-a,-a,-a);
    vertex(-a,-a,a);
    glEnd();
    glBegin(GL_POLYGON);
    vertex(a,a,a);
    vertex(a,a,-a);
    vertex(-a,a,-a);
    vertex(-a,a,a);
    glEnd();
    //TODO: Fix bad depth checking
    glBegin(GL_POLYGON);
    vertex(a,a,-a);
    vertex(a,-a,-a);
    vertex(-a,-a,-a);
    vertex(-a,a,-a);
    glEnd();
    glBegin(GL_POLYGON);
    vertex(a,a,a);
    vertex(a,-a,a);
    vertex(-a,-a,a);
    vertex(-a,a,a);
    glEnd();
    
    glutSwapBuffers();
    std::cout<<"Render end"<<std::endl;
}

void motionFunc(int x,int y){
    mouseX=x;
    mouseY=y;
}

void idle(){
    std::cout<<"Idle start"<<std::endl;
    glutPostRedisplay();
    std::cout<<"Idle end"<<std::endl;
}

int main(int argc, char **argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(175,175);
    glutInitWindowSize(windowWidth,windowHeight);
    glutCreateWindow("GL Window");
    glutDisplayFunc(render_scene);
    glutMotionFunc(motionFunc);
    glutPassiveMotionFunc(motionFunc);
    glutIdleFunc(idle);
    std::cout<<"Before glutMainLoop()"<<std::endl;
    glutMainLoop();
    std::cout<<"After glutMainLoop()"<<std::endl;
    usleep(1000);
    return 0;
}
