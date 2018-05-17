//
//  ShaderProgram.cpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/15/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(){
}

void ShaderProgram::compile(){
    vertID=compileShader(GL_VERTEX_SHADER, vertFileName);
    fragID=compileShader(GL_FRAGMENT_SHADER, fragFileName);
    progID=compileProgram(fragID, vertID);
}

void ShaderProgram::unBind(){
    glDeleteShader(fragID);
    glDeleteShader(vertID);
    glDeleteProgram(progID);
}

void ShaderProgram::glBind(){
    glUseProgram(progID);
}

void ShaderProgram::glAssignParams(){
}

