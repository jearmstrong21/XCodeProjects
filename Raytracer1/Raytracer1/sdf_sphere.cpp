//
//  sdf_sphere.cpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/5/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "sdf_sphere.hpp"

namespace sdf{
    
    float sdf_sphere::get_distance(vec3 p){
        return vec3::length(pos-p)-size;
    }
    
};
