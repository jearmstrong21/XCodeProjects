//
//  UIShader.hpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/17/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef UIShader_hpp
#define UIShader_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glfw3.h>
#include "VOGen.hpp"
#include "ShaderProgram.hpp"

class UIShader:public ShaderProgram{
public:
    UIShader();
    void glAssignParams();
};

#endif /* UIShader_hpp */
