//
//  shaders.cpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/15/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "shaders.hpp"

std::string readFileStr(std::string fileName){
    std::ifstream inFile;
    inFile.open(fileName);//open the input file
    if(inFile.fail()){
        std::cout<<"Cant find "<<fileName<<std::endl;
    }
    
    std::stringstream strStream;
    strStream << inFile.rdbuf();//read the file
    std::string str = strStream.str();//str holds the content of the file
    return str;
}
int compileShaderSource(GLenum shaderType, GLchar* shaderSource){
    unsigned int shaderID=glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    glCompileShader(shaderID);
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
    return shaderID;
}

int compileShader(GLenum shaderType,std::string shaderFile){
    std::string str=readFileStr(shaderFile);
//    std::cout<<"-------------------- begin: "<<shaderFile<<"--------------------\n"<<str<<"\n--------------------end: "<<shaderFile<<"--------------------\n";
    std::cout<<"Loaded "<<shaderFile<<"\n";
    return compileShaderSource(shaderType,(GLchar*)str.c_str());
}

unsigned int compileProgram(int frag,int vert){
    unsigned int prog=glCreateProgram();
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);
    glDeleteShader(vert);
    glDeleteShader(frag);
    return prog;
}

