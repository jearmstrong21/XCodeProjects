//
//  sdf_object.hpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/5/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef sdf_object_hpp
#define sdf_object_hpp

#include <stdio.h>

#include "vec3.hpp"

using math::vec3;

namespace sdf{

    class sdf_object{
    public:
        virtual float get_distance(vec3 pos);
    };
    
};

#endif /* sdf_object_hpp */
