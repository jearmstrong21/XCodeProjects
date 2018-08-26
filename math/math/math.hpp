//
//  math.hpp
//  math
//
//  Created by Jack Armstrong on 8/12/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef math_hpp
#define math_hpp

#include <stdio.h>
#include <cmath>

namespace math{
    int sign(float a);
    float abs(float a);
    float min(float a,float b);
    float max(float a,float b);
    float lerp(float t,float a,float b);
    float clamp(float t,float a,float b);
    float lin_norm(float t,float a,float b);
    float lin_remap(float t,float s1,float e1,float s2,float e2);
    bool is_in_range(float t,float a,float b);
};

#endif /* math_hpp */
