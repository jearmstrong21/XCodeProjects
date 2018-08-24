
//
//  rm.cpp
//  Raytracer
//
//  Created by Jack Armstrong on 8/23/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "rm.hpp"

namespace rm {
    
    float trace_scene(rm_scene scene, vec3 pos, vec3 dir,float mint,float maxt){
        int i=0;
        for(float t=mint;t<maxt&&i<RM_MAX_ITERS;){
            float h=scene(t*dir+pos);
            if(h<RM_EPSILON){
                return t;
            }
            i++;
            t+=h;
        }
        return -1;
    }
    
    float shadow_res(rm_scene scene, vec3 start,vec3 end,float mint){
        float maxt=vec3::length(end-start);
        vec3 dir=(end-start)/maxt;
        int i=0;
        float res=1;
        for(float t=mint;t<maxt&&i<RM_MAX_ITERS;){
            float h=scene(t*dir+start);
            if(h<RM_EPSILON*RM_EPSILON){
                return 0;
            }
            res=math::min(res,20*h/t);
            t+=h;
        }
        return res;
    }
    
    vec3 estimate_normal(rm_scene scene, vec3 p){
        return vec3::normalize(vec3(
                              scene(vec3(p.x + RM_EPSILON, p.y, p.z)) - scene(vec3(p.x - RM_EPSILON, p.y, p.z)),
                              scene(vec3(p.x, p.y + RM_EPSILON, p.z)) - scene(vec3(p.x, p.y - RM_EPSILON, p.z)),
                              scene(vec3(p.x, p.y, p.z + RM_EPSILON)) - scene(vec3(p.x, p.y, p.z - RM_EPSILON))
                              ));
    }
    
    vec3 cam_dir(vec2 uv,vec3 camPos,vec3 lookAt,float zoom){
        vec3 f = vec3::normalize(lookAt-camPos);
        vec3 r = vec3::cross(vec3(0., 1., 0.), f);
        vec3 u = vec3::cross(f, r);
        
        vec3 c = camPos + f*zoom;
        vec3 i = c + uv.x*r + uv.y*u;
        vec3 rayDirection = i-camPos;
        return vec3::normalize(rayDirection);
    }
    
};
