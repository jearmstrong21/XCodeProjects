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
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "ShaderProgram.hpp"
#include "Texture.hpp"

using std::string;
using std::vector;
using glm::vec3;
using glm::vec2;

struct Vertex {
    glm::vec3 pos;
    glm::vec3 col;
    glm::vec2 uv;
};

class VO{
public:
    unsigned int VBO,VAO,EBO;
    vector<Vertex>verts;
    vector<Texture>textures;
    vector<unsigned int>tris;
    VO();
    ~VO();
    
    void genBuffers(vector<Vertex>verts,vector<Texture>textures,vector<unsigned int>tris);
    void bindBuffers(ShaderProgram*shader);
    void delBuffers();
    
};

#endif /* VO_hpp */
