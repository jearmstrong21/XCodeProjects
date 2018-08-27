//
//  pt_aabb.hpp
//  Pathtracer
//
//  Created by Jack Armstrong on 8/27/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef pt_aabb_hpp
#define pt_aabb_hpp

#include <stdio.h>

#include "pt_obj.hpp"

namespace pt {
    
    class aabb : public obj {
    public:
        vec3 min;
        vec3 max;
        aabb();
        aabb(vec3 a,vec3 b);
        ~aabb();
        bool intersect(ray ray,float&t,vec3&n,obj*out_o)const;
    };
    
}

#endif /* pt_aabb_hpp */
