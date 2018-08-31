//
//  pt.hpp
//  Pathtracer
//
//  Created by Jack Armstrong on 8/26/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef pt_hpp
#define pt_hpp

#include <stdio.h>

#include "vec3.hpp"
#include "vec2.hpp"

using math::vec3;
using math::vec2;

namespace pt {
    struct ray {
        vec3 pos;
        vec3 dir;
        
        ray(vec3 p,vec3 d);
    };
    
    struct surface_data{
        vec3 normal;
        vec2 uv;
    };
    
    ray cam_ray(vec2 uv, vec3 camPos, vec3 lookAt, float zoom);
}

#endif /* pt_hpp */
