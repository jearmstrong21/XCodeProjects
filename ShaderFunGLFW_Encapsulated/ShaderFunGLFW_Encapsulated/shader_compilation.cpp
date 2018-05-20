//
//  shader_compilation.cpp
//  ShaderFunGLFW_Encapsulated
//
//  Created by Jack Armstrong on 5/19/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "shader_compilation.hpp"

GLshader compileShader(GLenum shaderType,string shaderSource,bool doErrorLog){
    GLshader shaderID=glCreateShader(shaderType);
    const GLchar* cstr=shaderSource.c_str();
    glShaderSource(shaderID, 1, &cstr, NULL);
    glCompileShader(shaderID);
    if(doErrorLog){
        int success;
        char infoLog[512];
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
            printf("ERROR::SHADER::");
            if(shaderType==GL_VERTEX_SHADER)printf("VERTEX");
            else if(shaderType==GL_FRAGMENT_SHADER)printf("FRAGMENT");
            else printf("NOSHADER");
            printf("::COMPILATION_FAILED\n");
            printf(infoLog);
            printf("\n");
            return -1;
        }
        
    }
    return shaderID;
}

GLshaderProgram compileProgram(GLshader frag, GLshader vert,bool doErrorLog){
    GLshaderProgram prog=glCreateProgram();
    glAttachShader(prog, frag);
    glAttachShader(prog, vert);
    glLinkProgram(prog);
    if(doErrorLog){
        int success;
        char infoLog[512];
        glGetProgramiv(prog, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(prog, 512, NULL, infoLog);
            std::cout<<"Linking failed, programID="<<prog<<", log: <"<<infoLog<<">\n";
        }
    }
    glDeleteShader(frag);
    glDeleteShader(vert);
    return prog;
}
