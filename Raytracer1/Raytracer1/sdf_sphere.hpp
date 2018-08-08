//
//  sdf_sphere.hpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/5/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef sdf_sphere_hpp
#define sdf_sphere_hpp

#include <stdio.h>

#include "sdf_object.hpp"

namespace sdf{
    
    class sdf_sphere : public sdf_object {
    public:
        vec3 pos;
        float size;
        
        float get_distance(vec3 p);
    };
    
};

#endif /* sdf_sphere_hpp */
