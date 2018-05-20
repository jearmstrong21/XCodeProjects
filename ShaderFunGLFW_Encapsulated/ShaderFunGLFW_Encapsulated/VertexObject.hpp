//
//  VertexObject.hpp
//  ShaderFunGLFW_Encapsulated
//
//  Created by Jack Armstrong on 5/19/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef VertexObject_hpp
#define VertexObject_hpp

#include <iostream>
#include <cstdio>
#include <cmath>
#include <OpenGL/gl3.h>
#include "glfw3.h"

class VertexObject{
public:
    
    unsigned int VBO,VAO,EBO;
    
    VertexObject();
    void initObjects(const float *vertices, const unsigned int *tris, int numVertices, int numTris);
    void bindObjects();
    void deleteObjects();
};


#endif /* VertexObject_hpp */
