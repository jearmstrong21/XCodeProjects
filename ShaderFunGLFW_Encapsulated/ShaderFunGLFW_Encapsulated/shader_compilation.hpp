//
//  shader_compilation.hpp
//  ShaderFunGLFW_Encapsulated
//
//  Created by Jack Armstrong on 5/19/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef shader_compilation_hpp
#define shader_compilation_hpp

#include <iostream>
#include <cstdio>
#include <cmath>
#include <OpenGL/gl3.h>
#include "glfw3.h"
#include <string>

using std::string;

typedef unsigned int GLshader;
typedef unsigned int GLshaderProgram;

GLshader compileShader(GLenum shaderType,string shaderSource,bool doErrorLog=true);
GLshaderProgram compileProgram(GLshader frag,GLshader vert,bool doErrorLog=true);

#endif /* shader_compilation_hpp */
