//
//  shaders.hpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/15/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef shaders_hpp
#define shaders_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
//#include <OpenGL/OpenGL.h>
#include <glfw3.h>

std::string readFileStr(std::string fileName);

int compileShaderSource(GLenum shaderType, GLchar* shaderSource);

int compileShader(GLenum shaderType,std::string shaderFile);

unsigned int compileProgram(int frag,int vert);

#endif /* shaders_hpp */
