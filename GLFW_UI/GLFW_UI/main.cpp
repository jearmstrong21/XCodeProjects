//
//  main.cpp
//  GLFW_UI
//
//  Created by Jack Armstrong on 5/30/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <iostream>
#include <glfw3.h>

int main(int argc, const char * argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window=glfwCreateWindow(1000, 1000, "GLFW UI", 0, 0);
    
    while(!glfwWindowShouldClose(window)){
        glfwMakeContextCurrent(window);
        
        glClearColor(0.25,0.25,0.25,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    return 0;
}
