
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
#include "VO.hpp"
#include "ShaderProgram.hpp"

bool hsb,smooth;
float xscale,yscale,maxIters;
int type;

void key_callback(GLFWwindow*window,int key,int scancode,int action,int mods){
    if(action==GLFW_RELEASE)return;
    if(action==GLFW_REPEAT)return;
    if(key==GLFW_KEY_M){
        type=0;
    }
    if(key==GLFW_KEY_J){
        type=1;
    }
    if(key==GLFW_KEY_S){
        smooth=!smooth;
    }
    if(key==GLFW_KEY_H){
        hsb=!hsb;
    }
}

int main(int argc, const char * argv[]) {
    type=0;
    hsb=false;
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
    float marg=1;
    float vertices[] = {
        marg,  marg, 0.0f,  // top right
        marg, -marg, 0.0f,  // bottom right
        -marg, -marg, 0.0f,  // bottom left
        -marg,  marg, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    glfwMakeContextCurrent(window);
    
    VO vo;
    vo.genBuffers(vertices, indices,sizeof(vertices),sizeof(indices));
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
//    glDeleteProgram(prog);
    vo.delBuffers();
    shader.del();
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    
    
    return 0;
}
