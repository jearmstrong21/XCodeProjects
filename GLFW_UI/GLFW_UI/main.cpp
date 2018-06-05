
//  main.cpp
//  GLFW_UI
//
//  Created by Jack Armstrong on 5/30/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <iostream>
#include <glfw3.h>
#include "VO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Letter.hpp"
#include "Math.hpp"

using glm::vec2;
using glm::vec3;
using glm::mat4;

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#define PI 3.14159265359

vec3 sphere(float theta,float phi,float r){
    return vec3(r*sin(theta)*cos(phi),r*sin(theta)*sin(phi),r*cos(theta));
}

int main(int argc, const char * argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window=glfwCreateWindow(1000, 1000, "GLFW UI", 0, 0);
    glfwMakeContextCurrent(window);


    vector<Letter>letters;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            Letter letter;
            letter.atlasX=i;
            letter.atlasY=j;
            letter.atlasW=10;
            letter.atlasH=10;
            Texture tex;
            tex.fileName="Textures/font.png";
            tex.genTexture(GL_NEAREST, GL_NEAREST);
            letter.tex=tex;
            letter.pos=vec3(Math::map(i,0,10,-1,1),Math::map(j,0,10,-1,1),0);
            letter.size=vec2(0.15,0.2);//fix size to uvoff ratio
            letter.uvoff=vec2(0.03,0.02);
            letter.init();
            letters.push_back(letter);
        }
    }
    
    while(!glfwWindowShouldClose(window)){
        glfwMakeContextCurrent(window);
        
        glClearColor(0.25,0.25,0.25,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
        
        for(Letter&letter:letters)letter.render();
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    for(Letter&letter:letters)letter.del();
    
    glfwTerminate();
    
    return 0;
}


