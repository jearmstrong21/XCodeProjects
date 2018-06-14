#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "VertexBuffer.h"
#include <vector>
using std::vector;

#include <iostream>

Vertex makeVert(float x,float y,float u,float v){
    Vertex vert;
    vert.pos=glm::vec3(x*2.0-1.0,y*2.0-1.0,0);
    vert.uv=glm::vec2(u,v);
    return vert;
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    
    const int arrW=200;
    const int arrH=200;
    float heights[arrW][arrH];
    float diff[arrW][arrH];
    
    float newHeights[arrW][arrH];
    float newDiff[arrW][arrH];
    
    for(int x=0;x<arrW;x++){
        for(int y=0;y<arrH;y++){
            heights[x][y]=cos( (x+y)*0.01 )*0.5+0.5;
//            heights[x][y]=0.0;
            diff[x][y]=0.0;
        }
    }
    
    // glfw window creation
    // --------------------
    
    float windowWidth=1000;
    float windowHeight=1000;
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "GLFW Heightfield water simulation", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    Shader shader;
    shader.vertFilename="shader.vert";
    shader.fragFilename="shader.frag";
    shader.loadFiles();
    shader.genProgram();
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    vector<Vertex>verts;
    vector<GLuint>tris;
    VertexBuffer vertexBuffer;

    float dx=1.0/arrW;
    float dy=1.0/arrH;
    for(int x=0;x<arrW;x++){
        for(int y=0;y<arrH;y++){
            Vertex v1=makeVert(x*dx, y*dy,        x*dx, y*dy);
            Vertex v2=makeVert(x*dx+dx, y*dy,     x*dx+dx, y*dy);
            Vertex v3=makeVert(x*dx+dx, y*dy+dy,  x*dx+dx, y*dy+dy);
            Vertex v4=makeVert(x*dx, y*dy+dy,     x*dx, y*dy+dy);
            int n=verts.size();
            verts.push_back(v1);
            verts.push_back(v2);
            verts.push_back(v3);
            verts.push_back(v4);
            tris.push_back(n+0);
            tris.push_back(n+1);
            tris.push_back(n+2);
            tris.push_back(n+0);
            tris.push_back(n+2);
            tris.push_back(n+3);
        }
    }
    
    vertexBuffer.bufferType=BUFFER_DYNAMIC;
    vertexBuffer.polygonType=RENDER_FILL;
    vertexBuffer.provokingVertex=VERTEX_FIRST;
    vertexBuffer.genBuffers(verts,tris);
    
    
    while (!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        double x,y;
        glfwGetCursorPos(window, &x, &y);
        
        y=windowHeight-y;
        x/=windowWidth;
        y/=windowHeight;
        x*=arrW;
        y*=arrH;
        
        int ix=(int)round(x);
        int iy=(int)round(y);
        
        int pressed=glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        
        for(int x=0;x<arrW;x++){
            for(int y=0;y<arrH;y++){
                newHeights[x][y]=heights[x][y];
                newDiff[x][y]=diff[x][y];
            }
        }
        for(int x=0;x<arrW;x++){
            for(int y=0;y<arrH;y++){
                float xmi=(x==0?heights[0][y]:heights[x-1][y]);
                float ymi=(y==0?heights[x][0]:heights[x][y-1]);
                float xpl=(x==arrW-1?heights[arrW-1][y]:heights[x+1][y]);
                float ypl=(y==arrH-1?heights[x][arrH-1]:heights[x][y+1]);
                newDiff[x][y]+=(xmi+xpl+ymi+ypl)/4-heights[x][y];
                newDiff[x][y]*=0.99;
                newHeights[x][y]+=newDiff[x][y];
                if(pressed==GLFW_PRESS&&glm::length(glm::vec2(x-ix,y-iy))<2.0)newHeights[x][y]=1.0;
            }
        }
        for(int x=0;x<arrW;x++){
            for(int y=0;y<arrH;y++){
                heights[x][y]=newHeights[x][y];
                diff[x][y]=newDiff[x][y];
            }
        }
        
        for(int x=0;x<arrW;x++){
            for(int y=0;y<arrH;y++){
                verts[ (x*arrH+y)*4].col.b=heights[x][y];
            }
        }
        
        shader.useProgram();
        vertexBuffer.updateBuffers(verts);
        vertexBuffer.bindBuffers();
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    vertexBuffer.deleteBuffers();
    shader.deleteProgram();
    
    glfwTerminate();
    return 0;
}
