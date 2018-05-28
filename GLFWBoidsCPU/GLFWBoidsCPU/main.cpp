
//  main.cpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/15/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include "BoxVO.hpp"
#include "ShaderProgram.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

using glm::mat4x4;
using glm::vec3;

bool hsb,smooth;
float xscale,yscale,maxIters;
int type;

void key_callback(GLFWwindow*window,int key,int scancode,int action,int mods){
    if(key==GLFW_KEY_1)maxIters++;
    if(key==GLFW_KEY_2)maxIters--;
    if(action==GLFW_RELEASE)return;
    if(action==GLFW_REPEAT)return;
    if(key==GLFW_KEY_T){
        if(type==0)type=1;
        else if(type==1)type=0;
    }
    if(key==GLFW_KEY_S){
        smooth=!smooth;
    }
    if(key==GLFW_KEY_H){
        hsb=!hsb;
    }
}

int main(int argc, const char * argv[]) {
    type=1;
    hsb=true;
    smooth=true;
    xscale=1;
    yscale=1;
    maxIters=50;
    
    if(!glfwInit()){
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window;
    window=glfwCreateWindow(1000, 1000, "Title", 0, 0);
    if(!window){
        glfwTerminate();
        return -1;
    }
    
    
    glfwMakeContextCurrent(window);
    
    BoxVO vo;
    vo.genBuffersBox(-1,-1,2,2);
    
    ShaderProgram shader;
    shader.vertFileName="shader.vert";
    shader.fragFileName="shader.frag";
    
    shader.compile();
    
    
    glfwSetKeyCallback(window, key_callback);
    
    while(!glfwWindowShouldClose(window)){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        xscale=(xpos/500)-1;
        yscale=(ypos/500)-1;
        
        glfwMakeContextCurrent(window);
        glClearColor(0.25,0.25,0.25,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        shader.setBool("doHSB", hsb);
        shader.setBool("doSmooth",smooth);
        shader.setFloat("xOffScale",xscale);
        shader.setFloat("yOffScale", yscale);
        shader.setFloat("maxIters", maxIters);
        shader.setInt("fractalType", type);
        
        shader.bind();
        vo.bindBuffers();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    vo.delBuffers();
    shader.del();
    
    glfwTerminate();
}
