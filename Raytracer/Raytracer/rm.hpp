//
//  rm.hpp
//  Raytracer
//
//  Created by Jack Armstrong on 8/23/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef rm_hpp
#define rm_hpp

#include <stdio.h>
#include "math/vec3.hpp"
#include "math/vec2.hpp"

using math::vec3;
using math::vec2;

#define RM_EPSILON 0.01
#define RM_MAX_ITERS 100

namespace rm{
    
    typedef float (*rm_scene)(vec3);
    
    float trace_scene(rm_scene scene,vec3 start,vec3 dir,float mint,float maxt);
    float shadow_res(rm_scene scene, vec3 start,vec3 end,float mint);
    vec3 estimate_normal(rm_scene scene,vec3 pos);
    
    vec3 cam_dir(vec2 uv,vec3 camPos,vec3 lookAt,float zoom);
}

#endif /* rm_hpp */
