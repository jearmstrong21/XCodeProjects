//
//  pt.cpp
//  Pathtracer
//
//  Created by Jack Armstrong on 8/26/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "pt.hpp"

namespace pt{
    
    ray::ray(vec3 p,vec3 d){
        pos=p;
        dir=d;
    }
    
    ray cam_ray(vec2 uv,vec3 camPos,vec3 lookAt,float zoom){
        vec3 f = vec3::normalize(lookAt-camPos);
        vec3 r = vec3::cross(vec3(0., 1., 0.), f);
        vec3 u = vec3::cross(f, r);
        
        vec3 c = camPos + f*zoom;
        vec3 i = c + uv.x*r + uv.y*u;
        vec3 rayDirection = i-camPos;
        return ray(camPos,vec3::normalize(rayDirection));
    }
    
}
