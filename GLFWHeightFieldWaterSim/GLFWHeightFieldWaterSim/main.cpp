//
//  main.cpp
//  GLFWHeightFieldWaterSim
//
//  Created by Jack Armstrong on 6/13/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

#include "VertexBuffer.hpp"

int main(int argc, const char * argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window=glfwCreateWindow(1000, 1000, "Heightfield water sim", 0, 0);
    glfwMakeContextCurrent(window);
    while(!glfwWindowShouldClose(window)){
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
