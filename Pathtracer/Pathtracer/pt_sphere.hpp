//
//  pt_sphere.hpp
//  Pathtracer
//
//  Created by Jack Armstrong on 8/26/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef pt_sphere_hpp
#define pt_sphere_hpp

#include <stdio.h>

#include "pt.hpp"
#include "pt_obj.hpp"

namespace pt {
    
    class sphere : public obj {
    public:
        float rad;
        vec3 center;
        
        sphere();
        ~sphere();
        sphere(vec3 c,float r);
        
        bool intersect(ray ray,float&t,surface_data&sd,pt::obj*out_o) const;
    };
    
}

#endif /* pt_sphere_hpp */
