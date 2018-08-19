//
//  vec3.hpp
//  Raytracer
//
//  Created by Jack Armstrong on 8/14/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef vec3_hpp
#define vec3_hpp

#include <stdio.h>
#include <cmath>

namespace math{
    struct vec3{
        float x;
        float y;
        float z;
        vec3();
        vec3(float xyz);
        vec3(float x,float y,float z);
        
        static float length(vec3 v);
        static float dot(vec3 a,vec3 b);
        static vec3 cross(vec3 a,vec3 b);
        static vec3 normalize(vec3 v);
        
        vec3& operator += (const vec3 rhs);
        vec3& operator -= (const vec3 rhs);
        vec3& operator *= (const vec3 rhs);
        vec3& operator /= (const vec3 rhs);
        
        vec3& operator += (const float rhs);
        vec3& operator -= (const float rhs);
        vec3& operator *= (const float rhs);
        vec3& operator /= (const float rhs);
    };
    
    vec3 operator + (vec3 a,vec3 b);
    vec3 operator - (vec3 a,vec3 b);
    vec3 operator * (vec3 a,vec3 b);
    vec3 operator / (vec3 a,vec3 b);
    
    vec3 operator + (vec3 a,float b);
    vec3 operator - (vec3 a,float b);
    vec3 operator * (vec3 a,float b);
    vec3 operator / (vec3 a,float b);
    
    vec3 operator + (float a,vec3 b);
    vec3 operator - (float a,vec3 b);
    vec3 operator * (float a,vec3 b);
    vec3 operator / (float a,vec3 b);
};

#endif /* vec3_hpp */
