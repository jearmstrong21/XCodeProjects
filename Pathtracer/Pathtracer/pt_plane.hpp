//
//  pt_plane.hpp
//  Pathtracer
//
//  Created by Jack Armstrong on 8/26/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef pt_plane_hpp
#define pt_plane_hpp

#include <stdio.h>

#include "pt_obj.hpp"

namespace pt {
    
    class plane : public obj {
    public:
        vec3 n;
        vec3 p0;
        plane();
        plane(vec3 n,vec3 p0);
        ~plane();
        
        bool intersect(ray ray,float&t,surface_data&sd,pt::obj*out_o)const;
    };
    
};

#endif /* pt_plane_hpp */
