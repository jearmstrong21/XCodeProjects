//
//  Math.cpp
//  GLFWBoidsCPU
//
//  Created by Jack Armstrong on 5/29/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "Math.hpp"

float Math::lerp(float start,float end,float t){
    return (1 - t) * start + t * end;
}

float Math::norm(float start,float end,float t){
    return (t-start)/(end-start);
}

float Math::map(float t,float start1,float end1,float start2,float end2){
    return Math::lerp(start2,end2,Math::norm(start1,end1,t));
}
