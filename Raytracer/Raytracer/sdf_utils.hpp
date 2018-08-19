//
//  sdf_utils.hpp
//  Raytracer
//
//  Created by Jack Armstrong on 8/17/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef sdf_utils_hpp
#define sdf_utils_hpp

#include <stdio.h>
#include "sdf.hpp"

namespace sdf{
    
    camera createCamera(vec2 uv,vec3 camPos,vec3 lookAt,float zoom);
    
    vec3 estimateNormal(sdf_scene scene,vec3 p);
    
    trace raymarch(sdf_scene scene,vec3 p,vec3 d);
}

#endif /* sdf_utils_hpp */
