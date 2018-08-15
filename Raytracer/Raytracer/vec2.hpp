//
//  vec2.hpp
//  Raytracer
//
//  Created by Jack Armstrong on 8/12/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef vec2_hpp
#define vec2_hpp

#include <stdio.h>
#include <cmath>

namespace math{
    
    struct vec2{
        float x;
        float y;
        vec2(float x,float y);
        vec2(float xy);
        vec2();
        static float length(vec2 v);
        static float dot(vec2 a,vec2 b);
        
        vec2& operator += (const vec2 rhs);
        vec2& operator -= (const vec2 rhs);
        vec2& operator *= (const vec2 rhs);
        vec2& operator /= (const vec2 rhs);
        
//        vec2& operator += (const float rhs);
//        vec2& operator -= (const float rhs);
        vec2& operator *= (const float rhs);
        vec2& operator /= (const float rhs);
    };
    
    vec2 operator + (vec2 a,vec2 b);
    vec2 operator - (vec2 a,vec2 b);
    vec2 operator * (vec2 a,vec2 b);
    vec2 operator / (vec2 a,vec2 b);
    
//    vec2 operator + (vec2 a,float b);
//    vec2 operator - (vec2 a,float b);
    vec2 operator * (vec2 a,float b);
    vec2 operator / (vec2 a,float b);
    
//    vec2 operator + (float a,vec2 b);
//    vec2 operator - (float a,vec2 b);
    vec2 operator * (float a,vec2 b);
//    vec2 operator / (float a,vec2 b);
    
};

#endif /* vec2_hpp */
