
//  Letter.cpp
//  GLFW_UI
//
//  Created by Jack Armstrong on 5/31/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "Letter.hpp"


Letter::Letter(){
    
}

void Letter::init(){
    float dx=1.0/atlasW;
    float dy=1.0/atlasH;
    float tx=dx*atlasX;
    float ty=dy*atlasY;
    vec2 texOff=vec2(0,0);
    
    Vertex v0;
    v0.pos=vec3(pos.x,pos.y,0);
    v0.uv=vec2(tx+uvoff.x,ty+uvoff.y);
    v0.col=vec3(1,1,1);
    Vertex v1;
    v1.pos=vec3(pos.x+size.x,pos.y,0);
    v1.uv=vec2(tx+dx-uvoff.x,ty+uvoff.y);
    v1.col=vec3(1,1,1);
    Vertex v2;
    v2.pos=vec3(pos.x+size.x,pos.y+size.y,0);
    v2.uv=vec2(tx+dx-uvoff.x,ty+dy-uvoff.y);
    v2.col=vec3(1,1,1);
    Vertex v3;
    v3.pos=vec3(pos.x,pos.y+size.y,0);
    v3.uv=vec2(tx+uvoff.x,ty+dy-uvoff.y);
    v3.col=vec3(1,1,1);
    std::cout<<tx<<" "<<ty<<","<<dx<<","<<dy<<"\n";
    vector<Vertex>verts;
    verts.push_back(v0);
    verts.push_back(v1);
    verts.push_back(v2);
    verts.push_back(v3);
    vector<Texture>texs;
    texs.push_back(tex);
    vector<unsigned int>tris;
    tris.push_back(0);
    tris.push_back(1);
    tris.push_back(2);
    tris.push_back(0);
    tris.push_back(2);
    tris.push_back(3);
    vo.genBuffers(verts, texs, tris);
    shader.vertFileName="Shaders/text.vert";
    shader.fragFileName="Shaders/text.frag";
    shader.compile();
    
}

void Letter::render(){
    vo.bindBuffers(&shader);
}

void Letter::del(){
    vo.delBuffers();
    shader.del();
}
