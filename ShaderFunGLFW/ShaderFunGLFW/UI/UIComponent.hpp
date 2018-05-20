//
//  UIComponent.hpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/17/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef UIComponent_hpp
#define UIComponent_hpp

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glfw3.h>
#include "VOGen.hpp"
#include "ShaderProgram.hpp"

class UIComponent{
public:
    VO vo;
    ShaderProgram shader;
    UIComponent();
    ~UIComponent();
    void render();
};

#endif /* UIComponent_hpp */
