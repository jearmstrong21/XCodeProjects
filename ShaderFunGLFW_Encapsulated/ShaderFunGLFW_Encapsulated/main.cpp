
//  main.cpp
//  ShaderFunGLFW_Encapsulated
//
//  Created by Jack Armstrong on 5/18/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <OpenGL/gl3.h>
#include "glfw3.h"
#include "VertexObject.hpp"
#include "shader_compilation.hpp"

int main(int argc, const char * argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    
    GLFWwindow* window=glfwCreateWindow(1000, 1000, "Window", 0, 0);


//    float vertices[] = {
//        0.5f,  0.5f, 0.0f,  // top right
//        0.5f, -0.5f, 0.0f,  // bottom right
//        -0.5f, -0.5f, 0.0f,  // bottom left
//        -0.5f,  0.5f, 0.0f   // top left
//    };
//    unsigned int tris[] = {  // note that we start from 0!
//        0, 1, 3,  // first Triangle
//        1, 2, 3   // second Triangle
//    };
//    VertexObject vo;
//    vo.initObjects(vertices, tris, 12, 6);

//    GLshader frag=compileShader(GL_FRAGMENT_SHADER, "#version 330 core\n"
//                                "out vec4 FragColor;\n"
//                                "void main(){\n"
//                                "    FragColor = vec4(1.0,0.0,0.0,1.0);\n"
//                                "}",true);
//    GLshader vert=compileShader(GL_VERTEX_SHADER, "#version 330 core\n"
//                                "layout(location = 0) in vec3 inPos;\n"
//                                "out vec4 outPos;\n"
//                                "void main(){\n"
//                                "   outPos=vec4(inPos.xyz,1.0);\n"
//                                "}",true);
//    GLshader frag=compileShader(GL_FRAGMENT_SHADER, "");
//    GLshader vert=compileShader(GL_VERTEX_SHADER, "");
//    glDeleteShader(frag);
//    glDeleteShader(vert);
//    GLshaderProgram prog=compileProgram(frag, vert);

    while(!glfwWindowShouldClose(window)){
        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
        glClearColor(0.25,0.25,0.25,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
