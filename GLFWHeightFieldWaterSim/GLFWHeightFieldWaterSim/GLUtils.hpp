//
//  GLUtils.hpp
//  GLFWHeightFieldWaterSim
//
//  Created by Jack Armstrong on 6/13/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef GLUtils_hpp
#define GLUtils_hpp

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <fstream>
#include <sstream>

string slurpFile(string fileName){
    std::ifstream t(fileName);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)


void printGLInfo(){
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    
    cout<<"Version ....... : "<<version<<endl;
    cout<<"Vendor ........ : "<<vendor<<endl;
    cout<<"Renderer ...... : "<<renderer<<endl;
    cout<<"GLSL Version .. : "<<glslVersion<<endl;
}

#endif /* GLUtils_hpp */
