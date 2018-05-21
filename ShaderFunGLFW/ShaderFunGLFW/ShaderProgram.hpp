//
//  ShaderProgram.hpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/19/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <OpenGL/gl3.h>
#include <glfw3.h>
#include "shaders.hpp"
#include "glm/mat4x4.hpp"

using glm::mat4x4;

using std::string;

class ShaderProgram{
public:
    string vertFileName;
    string fragFileName;
    int progID;
    
    ShaderProgram();
    ShaderProgram(string vertFile,string fragFile);
    ~ShaderProgram();
    
    void setBool(string param,bool b);
    void setFloat(string param,float f);
    void setInt(string param,int i);
    void setMat4x4(string param,mat4x4 mat);
    
    bool getBool(string param);
    float getFloat(string param);
    int getInt(string param);
    
    void compile();
    void bind();
    void del();
};


#endif /* ShaderProgram_hpp */
