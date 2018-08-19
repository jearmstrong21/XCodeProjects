//
//  sdf.hpp
//  Raytracer
//
//  Created by Jack Armstrong on 8/17/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef sdf_hpp
#define sdf_hpp

#include "vec3.hpp"
#include "vec2.hpp"
#include "math.hpp"
#include "complex.hpp"
#include "sdf_config.hpp"

using math::vec3;
using math::vec2;

namespace sdf{
    
    struct ray{
        vec3 pos;
        vec3 dir;
        
        ray(vec3 p,vec3 d);
    };
    
    struct trace {
        vec3 pos;
        vec3 dir;
        vec3 end;
        float total_d;
        float final_d;
        float min_d;
        int iters;
        bool completed;
    };
    
    typedef ray camera;
    
    typedef float (*sdf_scene)(vec3);
    
};

#endif /* sdf_hpp */
