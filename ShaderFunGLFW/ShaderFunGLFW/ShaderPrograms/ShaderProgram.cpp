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
    std::cout<<"ShaderProgram::compile():\n\tvertFileName="<<vertFileName<<"\n\tfragFileName="<<fragFileName<<"\n\tvertID="<<vertID<<"\n\tfragID="<<fragID<<"\n\tprogID="<<progID<<std::endl;
}

void ShaderProgram::assignSources(std::string vert,std::string frag){
    vertFileName=vert;
    fragFileName=frag;
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

