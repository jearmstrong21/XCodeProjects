//
//  UIWindow.cpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/17/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "UIWindow.hpp"
UIWindow::UIWindow(){
//    comps.push_back(UIComponent());
    
}
UIWindow::~UIWindow(){
    
}

void UIWindow::initWindow(){
    window=glfwCreateWindow(750,750,"UI Window",NULL,NULL);
}
void UIWindow::render(){
    glfwMakeContextCurrent(window);
    glClearColor(0.25,0.25,0.25,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    uic.shader.glAssignParams();
    uic.shader.glBind();
    uic.vo.bind();
//    glBindVertexArray(VAO);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}
