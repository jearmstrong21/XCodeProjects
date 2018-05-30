//
//  Boid.cpp
//  GLFWBoidsCPU
//
//  Created by Jack Armstrong on 5/28/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "Boid.hpp"

Boid::Boid(int theID){
    id=theID;
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
    
    pos=vec2(rand()%2000-1000.0f,rand()%2000-1000.0f)/1000.0f;
    vel=vec2(rand()%2000-1000.0f,rand()%2000-1000.0f)/1000.0f;
    acc=vec2(0,0);
}

void Boid::freeMem(){
    vo.delBuffers();
//    shader.del();
}

void Boid::update(vector<Boid>* boids, Params*params){
    wrapPos();
    acc=vec2(0,0);
    vec2 attractPosV2f;
    vec2 attractVelV2f;
    int num=0;
    for (const Boid &boid : *boids){
        if(boid.id==id)continue;
        float dist=length(boid.pos-pos);
//        if( dist<1 )continue;
        if(dist>params->boidAttractDist)continue;
        attractPosV2f+=boid.pos;
        attractVelV2f+=boid.vel;
        num++;
    }
    if(num!=0){
        attractPosV2f/=num;
        attractPosV2f-=pos;
        acc+=attractPosV2f*params->boidAttractPosMult;
        
        attractVelV2f/=num;
        attractVelV2f*=params->boidAttractVelMult;
        acc+=attractVelV2f;
    }
    
    num=0;
    vec2 sep;
    for(const Boid &boid:*boids){
        if(boid.id==id)continue;
        float dist=length(boid.pos-pos);
        if(dist<params->boidSepDist){
            sep-=boid.pos;
            num++;
        }
    }
    if(num!=0){
        sep/=num;
        sep+=pos;
        sep*=params->boidSepMult;
        acc+=sep;
    }
    
    
    
    vel+=acc;
    float velL=length(vel);
    if(velL>params->boidMaxVel){
        vel=normalize(vel)*params->boidMaxVel;
    }
    pos+=vel;
}

void Boid::wrapPos(){
    if(pos.x<-1)pos.x=1;
    if(pos.y<-1)pos.y=1;
    if(pos.x>1)pos.x=-1;
    if(pos.y>1)pos.y=-1;
}

void Boid::draw(Params*params,ShaderProgram* shader){
    float rot=atan2f(vel.x,vel.y);
//    float hue=Math::map(length(vel),0,params->boidMaxVel,0,360);
    float hue=Math::map(rot,-PI,PI,0,360);
    float r=Hue::hueToR(hue);
    float g=Hue::hueToG(hue);
    float b=Hue::hueToB(hue);
    shader->setFloat("colR", r);
    shader->setFloat("colG", g);
    shader->setFloat("colB", b);
    shader->setFloat("offX", pos.x);
    shader->setFloat("offY", pos.y);
    shader->setFloat("rot",rot-PI/2.0);
    shader->bind();
    vo.bindBuffers();
    
}
