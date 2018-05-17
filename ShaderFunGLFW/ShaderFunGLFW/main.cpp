//
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
#include "shaders.hpp"
#include "ShaderProgram.hpp"
#include "MandelbrotProgram.hpp"

int main(int argc, const char * argv[]) {
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
//    ShaderProgram shaderProgram=MandelbrotProgram();//its not finding the constructor
    MandelbrotProgram shaderProgram;
    glfwMakeContextCurrent(window);
    printf("Version: ");
    std::cout<<glGetString(GL_VERSION);
    printf("\n");
    printf("Renderer: ");
    std::cout<<glGetString(GL_RENDERER);
    printf("\n");
    
//    int shaderFrag=compileShader(GL_FRAGMENT_SHADER, "Shaders/shader.frag");
//    int shaderVert=compileShader(GL_VERTEX_SHADER  , "Shaders/shader.vert");
//    int shaderProg=compileProgram(shaderFrag, shaderVert);
    
//    glDeleteShader(shaderFrag);
//    glDeleteShader(shaderVert);
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
    unsigned int VBO, VAO, EBO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    int numFrames=0;
    
    double start,end,diff,fps;
    shaderProgram.compile();
    while(!glfwWindowShouldClose(window)){
        start=glfwGetTime();
        glClearColor(0.25,0.25,0.25,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//        shaderProgram.glAssignParams();
//        shaderProgram.glBind();
//        int MANDELBROT=0;
//        int JULIA=1;
//        GLint fractalType=glGetUniformLocation(shaderProg, "fractalType");
//        GLint xOffScale=glGetUniformLocation(shaderProg, "xOffScale");
//        GLint yOffScale=glGetUniformLocation(shaderProg, "yOffScale");
//        GLint maxIters=glGetUniformLocation(shaderProg, "maxIters");
//        GLint doHSB=glGetUniformLocation(shaderProg, "doHSB");
//        glUniform1i(fractalType, MANDELBROT);
//        glUniform1f(xOffScale,1);
//        glUniform1f(yOffScale,1);
//        glUniform1f(maxIters,cos(start*2)*20+25);
//        glUniform1i(doHSB, false);
//        glUseProgram(shaderProg);
        shaderProgram.glAssignParams();
        shaderProgram.glBind();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        numFrames++;
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        end=glfwGetTime();
        diff=end-start;//Seconds Per Frame
        fps=1.0/diff;
//        std::cout<<"FPS: "<<fps<<"\n";
//        glfwSetWindowTitle(window, std::string("Title, frameRate=").append(fps));
    }
    shaderProgram.unBind();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    
    
    return 0;
}
