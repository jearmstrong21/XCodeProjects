//
//  pt_sphere.cpp
//  Pathtracer
//
//  Created by Jack Armstrong on 8/26/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "pt_sphere.hpp"

namespace pt {
    
    sphere::sphere(){
        center=vec3(0);
        rad=0;
    }
    
    sphere::~sphere(){
        
    }
    
    sphere::sphere(vec3 c,float r){
        center=c;
        rad=r;
    }
    
    bool sphere::intersect(ray ray,float&t,vec3&n,pt::obj*out_o) const{
        out_o=(pt::obj*)this;
        float t0,t1;
        vec3 L=center-ray.pos;
        float tca=vec3::dot(L,ray.dir);
        float d2=vec3::dot(L,L)-tca*tca;
        if(d2>rad*rad)return false;
        float thc=sqrt(rad*rad-d2);
        t0=tca-thc;
        t1=tca+thc;
        
        if(t0>t1){
            std::swap(t0,t1);
        }
        
        if(t0<0){
            t0=t1;
            if(t0<0){
                t=0;
                return false;
            }
        }
        t=math::min(t0,t1);
        n=vec3::normalize(ray.pos+ray.dir*t-center);
        return true;
    }
    
}
