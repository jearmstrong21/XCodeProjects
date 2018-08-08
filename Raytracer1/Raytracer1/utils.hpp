//
//  utils.hpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/5/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include "mat3.hpp"
#include "vec2.hpp"
#include "vec3.hpp"

using math::mat3;
using math::vec2;
using math::vec3;

struct ray {
    vec3 pos;
    vec3 dir;
};

ray cam_ray(vec2 uv, vec3 camPos, vec3 lookAt, float zoom);
mat3 view_matrix(vec3 eye,vec3 center,vec3 up);

namespace math {
    
    float max(float a,float b);
    float min(float a,float b);
    
    float norm(float t,float a,float b);
    float lerp(float t,float a,float b);
    float clamp(float t,float a,float b);
    bool isInRange(float t,float a,float b);
    float lin_remap(float t,float s1,float e1,float s2,float e2);

};

namespace color {
    
    float thetaToR(float theta);
    float thetaToG(float theta);
    float thetaToB(float theta);
    
};



#endif /* utils_hpp */
