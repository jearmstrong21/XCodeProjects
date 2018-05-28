//
//  BoxVO.cpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/20/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "BoxVO.hpp"


BoxVO::BoxVO(){
    
}

BoxVO::~BoxVO(){
    
}

void BoxVO::genBuffersBox(float x, float y, float w, float h){
    float vertices[] = {
        x+w,  y+h, 0.0f,  // top right
        x+w, y, 0.0f,  // bottom right
        x, y, 0.0f,  // bottom left
        x,  y+h, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3,   // second Triangle
        3,1,0, 3,2,1
    };
    genBuffers(vertices, indices, sizeof(vertices), sizeof(indices));
}
