//
//  hsv.cpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/12/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "hsv.hpp"

namespace colors{
    float h2r(float theta) {//in range 0 to 1
        while(theta<0)theta+=1;
        while(theta>1)theta-=1;
        theta*=360;
        if(math::is_in_range(theta, 0, 60))return 1;
        if(math::is_in_range(theta, 60, 120))return math::lin_remap(theta, 60, 120, 1, 0);
        if(math::is_in_range(theta, 120, 180))return 0;
        if(math::is_in_range(theta, 180, 240))return 0;
        if(math::is_in_range(theta, 240, 300))return math::lin_remap(theta, 240, 300, 0, 1);
        if(math::is_in_range(theta, 300, 360))return 1;
        return 0;
    }
    
    float h2g(float theta) {//in range 0 to 1
        while(theta<0)theta+=1;
        while(theta>1)theta-=1;
        theta*=360;
        if(math::is_in_range(theta, 0, 60))return math::lin_remap(theta, 0, 60, 0, 1);
        if(math::is_in_range(theta, 60, 120))return 1;
        if(math::is_in_range(theta, 120, 180))return 1;
        if(math::is_in_range(theta, 180, 240))return math::lin_remap(theta, 180, 240, 1, 0);
        if(math::is_in_range(theta, 240, 300))return 0;
        if(math::is_in_range(theta, 300, 360))return 0;
        return 0;
    }
    
    float h2b(float theta) {//in range 0 to 1
        while(theta<0)theta+=1;
        while(theta>1)theta-=1;
        theta*=360;
        if(math::is_in_range(theta, 0, 60))return 0;
        if(math::is_in_range(theta, 60, 120))return 0;
        if(math::is_in_range(theta, 120, 180))return math::lin_remap(theta, 120, 180, 0, 1);
        if(math::is_in_range(theta, 180, 240))return 1;
        if(math::is_in_range(theta, 240, 300))return 1;
        if(math::is_in_range(theta, 300, 360))return math::lin_remap(theta, 300, 360, 1, 0);
        return 0;
    }
};
