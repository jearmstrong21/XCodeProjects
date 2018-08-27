//
//  pt_list.hpp
//  Pathtracer
//
//  Created by Jack Armstrong on 8/26/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef pt_list_hpp
#define pt_list_hpp

#include <stdio.h>

#include "pt_obj.hpp"

#include <vector>

using std::vector;

namespace pt {
    
    class list : public obj {
    public:
//        list();
//        ~list();
        vector<std::unique_ptr<obj>>inner;
        void clear();
        int size()const;
        void add(obj *o);
        bool intersect(ray ray,float &t,vec3&n,pt::obj*o) const;
    };
    
}

#endif /* pt_list_hpp */
