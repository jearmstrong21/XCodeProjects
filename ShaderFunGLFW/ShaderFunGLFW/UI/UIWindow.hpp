//
//  UIWindow.hpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/17/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef UIWindow_hpp
#define UIWindow_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glfw3.h>
#include <vector>
#include "UIComponent.hpp"
using std::vector;

class UIWindow{
public:
    UIComponent uic;
    GLFWwindow* window;
    
    vector<UIComponent>comps;
    UIWindow();
    ~UIWindow();
    
    void initWindow();
    void render();
};

#endif /* UIWindow_hpp */
