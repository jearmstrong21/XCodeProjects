//
//  Mesh.cpp
//  GLFWBoidsCPU
//
//  Created by Jack Armstrong on 5/27/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "Mesh.hpp"

Mesh::Mesh(){
    
}

void Mesh::initMesh(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), &verts[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tris.size() * sizeof(unsigned int),
                 &tris[0], GL_STATIC_DRAW);
    
    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    
    glBindVertexArray(0);
}

void Mesh::drawMesh(ShaderProgram shader){
    int nr=1;
    for(unsigned int i = 0; i < texs.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        string number;
        
        number = std::to_string(nr++);
        
        shader.setFloat("texture", i);
        glBindTexture(GL_TEXTURE_2D, texs[i].id);
    }
    glActiveTexture(GL_TEXTURE0);
    
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, tris.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::delMesh(){
}
