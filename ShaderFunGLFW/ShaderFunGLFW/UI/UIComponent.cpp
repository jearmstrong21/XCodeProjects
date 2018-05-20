//
//  UIComponent.cpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/17/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "UIComponent.hpp"

UIComponent::UIComponent(){
    vo.gen(0,0,0.5,0.5);
    shader.assignSources("uidefault.vert","uidefault.frag");
    shader.compile();
}

UIComponent::~UIComponent(){
    shader.unBind();
}

void UIComponent::render(){
    shader.glAssignParams();
    shader.glBind();
    vo.bind();
}
