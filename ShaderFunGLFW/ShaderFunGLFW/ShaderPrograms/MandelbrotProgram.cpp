//
//  MandelbrotProgram.cpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/15/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "MandelbrotProgram.hpp"

MandelbrotProgram::MandelbrotProgram(){
    this->fragFileName="shader.frag";
    this->vertFileName="shader.vert";
}

void MandelbrotProgram::glAssignParams(){
    int MANDELBROT=0;
    int JULIA=1;
    GLint fractalType=glGetUniformLocation(progID, "fractalType");
    GLint xOffScale=glGetUniformLocation(progID, "xOffScale");
    GLint yOffScale=glGetUniformLocation(progID, "yOffScale");
    GLint maxIters=glGetUniformLocation(progID, "maxIters");
    GLint doHSB=glGetUniformLocation(progID, "doHSB");
    GLint doSmooth=glGetUniformLocation(progID, "doSmooth");
    glUniform1i(fractalType, MANDELBROT);
    glUniform1f(xOffScale,1);
    glUniform1f(yOffScale,1);
    //        glUniform1f(maxIters,(int)(cos(glfwGetTime()*2)*200+210));
    glUniform1f(maxIters, 50);
    glUniform1i(doHSB, false);
    glUniform1i(doSmooth, false);
}
