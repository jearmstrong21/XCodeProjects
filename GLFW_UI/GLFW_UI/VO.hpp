//
//  VO.hpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/19/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef VO_hpp
#define VO_hpp

#include <iostream>
#include <cstdio>
#include <cmath>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

class VO{
public:
    unsigned int VBO,VAO,EBO;
    VO();
    ~VO();
    
    void genBuffers(float verts[], unsigned int tris[],float texCoords[],std::size_t vertsSize,std::size_t triSize,std::size_t texCoordSize);
    void bindBuffers();
    void delBuffers();
    
};

#endif /* VO_hpp */
