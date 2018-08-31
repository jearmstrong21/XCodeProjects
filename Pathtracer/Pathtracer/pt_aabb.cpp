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
    
    bool aabb::intersect(ray ray,float&t,surface_data&sd,pt::obj*out_o)const{
        out_o=(pt::obj*)this;
        sd.normal=vec3(0);
        sd.uv=vec2(0);
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
        float u=math::lin_remap(end.x,min.x,max.x,0,1);
        float v=math::lin_remap(end.y,min.y,max.y,0,1);
        float w=math::lin_remap(end.z,min.z,max.z,0,1);
        if(end.x<min.x){sd.normal=vec3(-1,0,0);sd.uv=vec2(v,w);}
        if(end.x>max.x){sd.normal=vec3(1,0,0) ;sd.uv=vec2(v,w);}
        if(end.y<min.y){sd.normal=vec3(0,-1,0);sd.uv=vec2(u,w);}
        if(end.y>max.y){sd.normal=vec3(0,1,0) ;sd.uv=vec2(u,w);}
        if(end.z<min.z){sd.normal=vec3(0,0,-1);sd.uv=vec2(u,v);}
        if(end.z>max.z){sd.normal=vec3(0,0,1) ;sd.uv=vec2(u,v);}
        
        return true;
    }
}
