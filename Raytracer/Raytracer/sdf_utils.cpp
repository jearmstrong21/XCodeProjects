//
//  sdf_utils.cpp
//  Raytracer
//
//  Created by Jack Armstrong on 8/17/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "sdf_utils.hpp"

namespace sdf{
    
    camera createCamera(vec2 uv,vec3 camPos,vec3 lookAt,float zoom){
        vec3 rayPos = camPos;
        
        
        vec3 f = vec3::normalize(lookAt-rayPos);
        vec3 r = vec3::cross(vec3(0., 1., 0.), f);
        vec3 u = vec3::cross(f, r);
        
        vec3 c = rayPos + f*zoom;
        vec3 i = c + uv.x*r + uv.y*u;
        vec3 rayDirection = i-rayPos;
        return camera(rayPos,vec3::normalize(rayDirection));
    }
    
    vec3 estimateNormal(sdf_scene scene,vec3 p){
        return vec3::normalize(vec3(
                              scene(vec3(p.x + EPSILON, p.y, p.z)) - scene(vec3(p.x - EPSILON, p.y, p.z)),
                              scene(vec3(p.x, p.y + EPSILON, p.z)) - scene(vec3(p.x, p.y - EPSILON, p.z)),
                              scene(vec3(p.x, p.y, p.z  + EPSILON)) - scene(vec3(p.x, p.y, p.z - EPSILON))
                              ));
    }
    
}
