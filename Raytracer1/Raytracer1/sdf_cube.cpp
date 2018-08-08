//
//  sdf_cube.cpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/5/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "sdf_cube.hpp"

namespace sdf{
    
    float sdf_cube::get_distance(vec3 p){
        p-=pos;
        p/=size;
        // If d.x < 0, then -1 < p.x < 1, and same logic applies to p.y, p.z
        // So if all components of d are negative, then p is inside the unit cube
        vec3 d = vec3::abs(p) - vec3(1.0, 1.0, 1.0);
        
        // Assuming p is inside the cube, how far is it from the surface?
        // Result will be negative or zero.
        float insideDistance = math::min(math::max(d.x, math::max(d.y, d.z)), 0.0);
        
        // Assuming p is outside the cube, how far is it from the surface?
        // Result will be positive or zero.
        float outsideDistance = vec3::length(vec3::max(d, 0.0));
        
        return insideDistance + outsideDistance;
    }
    
};
