//
//  ShaderProgram.cpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/19/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "ShaderProgram.hpp"


ShaderProgram::ShaderProgram(){
    
}

ShaderProgram::ShaderProgram(string vertFile,string fragFile){
    vertFileName=vertFile;
    fragFileName=fragFile;
}

ShaderProgram::~ShaderProgram(){
    
}

void ShaderProgram::compile(){
    unsigned int vert=compileShader(GL_VERTEX_SHADER, "shader.vert");
    unsigned int frag=compileShader(GL_FRAGMENT_SHADER, "shader.frag");
    progID=compileProgram(frag, vert);
}

void ShaderProgram::bind(){
    glUseProgram(progID);
}

void ShaderProgram::del(){
    glDeleteProgram(progID);
}

void ShaderProgram::setBool(string param, bool b){
    glUniform1i(glGetUniformLocation(progID, param.c_str()), b);
}

void ShaderProgram::setFloat(string param,float f){
    glUniform1f(glGetUniformLocation(progID, param.c_str()),f);
}

void ShaderProgram::setInt(string param,int i){
    glUniform1i(glGetUniformLocation(progID, param.c_str()), i);
}

void ShaderProgram::setMat4x4(string param,mat4x4 mat){
    glUniformMatrix4fv(glGetUniformLocation(progID, param.c_str()), 1, GL_FALSE, &mat[0][0]);
}

bool ShaderProgram::getBool(string param){
    int b;
    glGetUniformiv(progID, glGetUniformLocation(progID, param.c_str()), &b);
    return b;
}

float ShaderProgram::getFloat(string param){
    float f;
    glGetUniformfv(progID, glGetUniformLocation(progID, param.c_str()), &f);
    return f;
}

int ShaderProgram::getInt(string param){
    int i;
    glGetUniformiv(progID, glGetUniformLocation(progID, param.c_str()), &i);
    return i;
}
