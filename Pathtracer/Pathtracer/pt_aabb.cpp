//
//  pt_aabb.cpp
//  Pathtracer
//
//  Created by Jack Armstrong on 8/27/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "pt_aabb.hpp"

namespace pt {
    
    aabb::aabb(){
        
    }
    
    aabb::aabb(vec3 a,vec3 b){
        min=a;
        max=b;
    }
    
    aabb::~aabb(){
        
    }
    
    bool aabb::intersect(ray ray,float&t,vec3&out_n,pt::obj*out_o)const{
        out_o=(pt::obj*)this;
        out_n=vec3(0);
        t=0;
        
        
        float tmin=(min.x-ray.pos.x)/ray.dir.x;
        float tmax=(max.x-ray.pos.x)/ray.dir.x;
        
        if(tmin>tmax)std::swap(tmin,tmax);
        
        float tymin=(min.y-ray.pos.y)/ray.dir.y;
        float tymax=(max.y-ray.pos.y)/ray.dir.y;
        
        if(tymin>tymax)std::swap(tymin,tymax);
        
        if(tmin>tymax||tymin>tmax){
            return false;
        }
        
        if(tymin>tmin){
            tmin=tymin;
        }
        
        if(tymax<tmax){
            tmax=tymax;
        }
        
        float tzmin=(min.z-ray.pos.z)/ray.dir.z;
        float tzmax=(max.z-ray.pos.z)/ray.dir.z;
        
        if(tzmin>tzmax)std::swap(tzmin,tzmax);
        
        if(tmin>tzmax||tzmin>tmax){
            return false;
        }
        
        if(tzmin>tmin){
            tmin=tzmin;
        }
        
        if(tzmax<tmax){
            tmax=tzmax;
        }
        
        t=tmin;
        
        if(t<0){
            t=tmax;
            if(t<0)return false;
        }
        
        vec3 end=ray.pos+(t-1e-6)*ray.dir;
        if(end.x<min.x)out_n=vec3(-1,0,0);
        if(end.x>max.x)out_n=vec3(1,0,0);
        if(end.y<min.y)out_n=vec3(0,-1,0);
        if(end.y>max.y)out_n=vec3(0,1,0);
        if(end.z<min.z)out_n=vec3(0,0,-1);
        if(end.z>max.z)out_n=vec3(0,0,1);
        
        return true;
    }
}
