//
//  main.cpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/15/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include "shaders.hpp"

#include <chrono>

// ...

using namespace std::chrono;
milliseconds getMillis(){
    return duration_cast< milliseconds >(system_clock::now().time_since_epoch());
}

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
    
    glfwMakeContextCurrent(window);
    printf("Version: ");
    std::cout<<glGetString(GL_VERSION);
    printf("\n");
    printf("Renderer: ");
    std::cout<<glGetString(GL_RENDERER);
    printf("\n");
    
    int shaderFrag=compileShader(GL_FRAGMENT_SHADER, "shader.frag");
    int shaderVert=compileShader(GL_VERTEX_SHADER  , "shader.vert");
    int shaderProg=compileProgram(shaderFrag, shaderVert);
    
    glDeleteShader(shaderFrag);
    glDeleteShader(shaderVert);
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
    milliseconds start,end;
    while(!glfwWindowShouldClose(window)){
        start=getMillis();
        glClearColor(0.25,0.25,0.25,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProg);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
//        printf("END RENDER: ");
        std::cout<<numFrames;
        printf("\n");
        numFrames++;
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        end=getMillis();
        std::cout<<(end.count()-start.count())<<"\n";
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();

    
    return 0;
}
