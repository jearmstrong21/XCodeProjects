//
//  VertexBuffer.h
//  GLFWHeightFieldWaterSim
//
//  Created by Jack Armstrong on 6/13/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef VertexBuffer_h
#define VertexBuffer_h

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include "GLUtils.hpp"
#include <vector>
using std::vector;
#include <glm/glm.hpp>

#define RENDER_FILL GL_FILL
#define RENDER_WIREFRAME GL_LINE

#define BUFFER_DYNAMIC GL_DYNAMIC_DRAW
#define BUFFER_STATIC GL_STATIC_DRAW

#define VERTEX_FIRST GL_FIRST_VERTEX_CONVENTION
#define VERTEX_LAST GL_LAST_VERTEX_CONVENTION

struct Vertex{
    glm::vec3 pos;
    glm::vec3 col;
    glm::vec2 uv;
};

class VertexBuffer{
    
public:
    
    GLuint vao,vbo,ebo;
    
    vector<Vertex>verts;
    vector<GLuint>tris;
    
    GLenum bufferType;
    GLenum polygonType;
    GLenum provokingVertex;
    
    void genBuffers(vector<Vertex> _verts, vector<GLuint> _tris){
        verts=_verts;
        tris=_tris;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        
        glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), &verts[0], bufferType);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, tris.size() * sizeof(GLuint),
                     &tris[0], bufferType);
        
        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        
        glBindVertexArray(0);
    };
    void updateBuffers(vector<Vertex>_verts){
        verts=_verts;
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        
        glBufferSubData(GL_ARRAY_BUFFER, 0, verts.size()*sizeof(Vertex), &verts[0]);
        
        glBindVertexArray(0);
    }
    void bindBuffers(){
        
        glPolygonMode(GL_FRONT_AND_BACK, polygonType);
        glProvokingVertex(provokingVertex);
        glBindVertexArray(vao); // seeing as we only have a single vao there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, tris.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    };
    void deleteBuffers(){
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    };
    
};


#endif /* VertexBuffer_h */
