//
//  pt_obj.hpp
//  Pathtracer
//
//  Created by Jack Armstrong on 8/26/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef pt_obj_hpp
#define pt_obj_hpp

#include <stdio.h>

#include "pt.hpp"

namespace pt {

    class obj {
    public:
        obj();
        ~obj();
        virtual bool intersect(ray ray,float &t,vec3&n,pt::obj*o) const = 0;
    };

}

#endif /* pt_obj_hpp */
