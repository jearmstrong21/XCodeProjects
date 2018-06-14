//
//  Shader.h
//  GLFWHeightFieldWaterSim
//
//  Created by Jack Armstrong on 6/13/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef Shader_h
#define Shader_h

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include "GLUtils.hpp"
#include <string>
using std::string;

namespace ShaderUtils{
    GLuint compileShader(GLenum shaderType, string shaderSource, string shaderTypeStr){
        int shaderID = glCreateShader(shaderType);
        const GLchar* cstr=shaderSource.c_str();
        glShaderSource(shaderID, 1, &cstr, NULL);
        glCompileShader(shaderID);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::"<<shaderTypeStr<<"::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        return shaderID;
    }
    GLuint linkProgram(GLuint vert, GLuint frag){
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vert);
        glAttachShader(shaderProgram, frag);
        glLinkProgram(shaderProgram);
        // check for linking errors
        int success;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vert);
        glDeleteShader(frag);
        return shaderProgram;
    }
};


class Shader{
public:
    
    GLuint programID;
    
    string vertCode,fragCode,vertFilename,fragFilename;
    
    Shader(){
        
    };
    
    void loadFiles(){
        vertCode=slurpFile(vertFilename);
        fragCode=slurpFile(fragFilename);
    };
    void genProgram(){
        int vertexShader = ShaderUtils::compileShader(GL_VERTEX_SHADER, slurpFile(vertFilename), "vertex");
        // fragment shader
        int fragmentShader = ShaderUtils::compileShader(GL_FRAGMENT_SHADER, slurpFile(fragFilename), "fragment");
        programID=ShaderUtils::linkProgram(vertexShader, fragmentShader);
    };
    void useProgram(){
        glUseProgram(programID);
    };
    void deleteProgram(){
        glDeleteProgram(programID);
    };
    
};


#endif /* Shader_h */
