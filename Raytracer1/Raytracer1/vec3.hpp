//
//  vec3.hpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/3/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef vec3_hpp
#define vec3_hpp

#include <stdio.h>
#include <cmath>
#include "utils.hpp"

namespace math {
    
    class vec3 {
    private:
    public:
        float x;
        float y;
        float z;
        vec3();
        vec3(float x,float y,float z);
        vec3(const vec3 &other);
        
        vec3 operator + (vec3 other);
        vec3 operator - (vec3 other);
        vec3 operator * (vec3 other);
        vec3 operator / (vec3 other);
        
        vec3 operator * (float other);
        vec3 operator / (float other);
        
        vec3 operator - (void);
        
        vec3& operator += (const vec3& rhs);
        vec3& operator -= (const vec3& rhs);
        vec3& operator *= (const vec3& rhs);
        vec3& operator /= (const vec3& rhs);
        
        
        vec3& operator += (const float& rhs);
        vec3& operator -= (const float& rhs);
        vec3& operator *= (const float& rhs);
        vec3& operator /= (const float& rhs);
        
        static vec3 max(vec3 a,vec3 b);
        static vec3 max(vec3 a,float b);
        static vec3 max(float a,vec3 b);
        
        static vec3 cross(vec3 a, vec3 b);
        
        static float dot(vec3 a, vec3 b);
        
        static float length(vec3 a);
        
        static vec3 mod(vec3 a,float b);
        static vec3 u_mod(vec3 a,float b);
        
        static vec3 abs(vec3 p);
        
        static vec3 normalize(vec3 a);
    };
    
    vec3 operator * (float a,vec3 b);
};

#endif /* vec3_hpp */
