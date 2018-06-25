
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
#include "Boid.hpp"
#include "Params.hpp"
#include <vector>

using std::vector;

int main(int argc, const char * argv[]) {
    
    if(!glfwInit()){
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window;
    float min=1000;
    window=glfwCreateWindow(min, min, "Title", 0, 0);
    if(!window){
        glfwTerminate();
        return -1;
    }
    
    
    glfwMakeContextCurrent(window);

    
    Params params;
    params.boidSize=0.01;
    params.boidAttractDist=0.05;
    params.boidAttractPosMult=0.5;
    params.boidAttractVelMult=50;
    params.boidSepMult=0.25;
    params.boidSepDist=0.02;
    params.boidMaxVel=0.01;
    params.boidStayInBorders=0.001;
    params.boidMinPos=vec2(-0.75,-0.75);
    params.boidMaxPos=vec2( 0.75, 0.75);
    params.boidWorldCenter=vec2(0,0);
    
    vector<Boid>boids;
    
    ShaderProgram shader;
    shader.vertFileName="boid.vert";
    shader.fragFileName="boid.frag";
    shader.compile();
    
    for(int i=0;i<500;i++){
        Boid boid(i);
        boid.init(&params);
        boids.push_back(boid);
    }
    
    while(!glfwWindowShouldClose(window)){
        glfwMakeContextCurrent(window);
        glClearColor(0.25,0.25,0.25,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        for(int i=0;i<boids.size();i++){
            boids[i].draw(&params, &shader);
            boids[i].update(&boids, &params);
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    for(int i=0;i<boids.size();i++){
        boids[i].freeMem();
    }
    shader.del();
    
    glfwTerminate();
}
