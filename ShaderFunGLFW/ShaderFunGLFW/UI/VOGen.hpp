//
//  VOGen.hpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/17/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef VOGen_hpp
#define VOGen_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glfw3.h>
#include <OpenGL/gl3.h>

class VO{
public:
    unsigned int EBO,VAO,VBO;
    float x,y,w,h;
    void gen(float x,float y,float w,float h);
    VO();
    ~VO();
    void bind();
};

#endif /* VOGen_hpp */
