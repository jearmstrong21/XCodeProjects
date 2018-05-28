//
//  Mesh.hpp
//  GLFWBoidsCPU
//
//  Created by Jack Armstrong on 5/27/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include "ShaderProgram.hpp"

using std::vector;
using std::string;
using glm::vec3;
using glm::vec2;

struct Vertex{
    vec3 pos;
    vec3 col;
    vec2 texCoords;
};

struct Texture{
    unsigned int id;
};

class Mesh{
public:
    vector<Vertex>verts;
    vector<unsigned int>tris;
    vector<Texture>texs;
    Mesh();
    void initMesh();
    void delMesh();
    void drawMesh(ShaderProgram shader);
    unsigned int VBO,VAO,EBO;
};

#endif /* Mesh_hpp */
