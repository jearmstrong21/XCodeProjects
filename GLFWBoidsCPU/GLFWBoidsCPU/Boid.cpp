//
//  Boid.cpp
//  GLFWBoidsCPU
//
//  Created by Jack Armstrong on 5/28/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "Boid.hpp"

Boid::Boid(){
    
}

void Boid::init(Params* params){
    float verts[]={
        -1*params->boidSize,0.5f*params->boidSize,0,
        -1*params->boidSize,-0.5f*params->boidSize,0,
        1*params->boidSize,0,0
    };
    unsigned int tris[]={
        0,1,2
    };
    vo.genBuffers(verts, tris, sizeof(verts), sizeof(tris));
    shader.vertFileName="boid.vert";
    shader.fragFileName="boid.frag";
    shader.compile();
    
    pos=vec2(0,0);
    vel=vec2(0.01,0.0025);
    acc=vec2(0,0);
}

void Boid::update(){
    wrap();
    pos+=vel;
    vel+=acc;
}

void Boid::wrap(){
    if(pos.x<-1)pos.x=1;
    if(pos.y<-1)pos.y=1;
    if(pos.x>1)pos.x=-1;
    if(pos.y>1)pos.y=-1;
}

void Boid::draw(){
    float t=glfwGetTime()/3;
    vel=vec2(cos(t)*0.01,sin(t)*0.01);
    shader.setFloat("colR", 1);
    shader.setFloat("colG", 1);
    shader.setFloat("colB", 1);
    shader.setFloat("offX", pos.x);
    shader.setFloat("offY", pos.y);
    shader.setFloat("rot",angle(vel.x,vel.y)-PI/2);
    shader.bind();
    vo.bindBuffers();
    
}
