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

#define PI 3.1415926536
#define TWO_PI 6.2831853072
#define HALF_PI 1.5707963268

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
    bool solve_quadratic(float a,float b,float c,float&r1,float&r2);
};

#endif /* math_hpp */
