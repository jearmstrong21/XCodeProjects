//
//  vec2.hpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/5/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef vec2_hpp
#define vec2_hpp

#include <stdio.h>
#include <cmath>

namespace math{
    
    class vec2{
    private:
    public:
        float x;
        float y;
        vec2();
        vec2(float x,float y);
        vec2(const vec2 &other);
        
        vec2 operator + (vec2 &other);
        vec2 operator - (vec2 &other);
        vec2 operator * (vec2 &other);
        vec2 operator / (vec2 &other);
        
        vec2 operator * (float other);
        vec2 operator / (float other);
        
        vec2& operator += (const vec2& rhs);
        vec2& operator -= (const vec2& rhs);
        vec2& operator *= (const vec2& rhs);
        vec2& operator /= (const vec2& rhs);
        
        vec2& operator += (const float& rhs);
        vec2& operator -= (const float& rhs);
        vec2& operator *= (const float& rhs);
        vec2& operator /= (const float& rhs);
        
        vec2 operator - (void);
        
        static float dot(vec2 a, vec2 b);
        
        float length();
        
        vec2 normalize();
    };
    
    vec2 operator * (float a,vec2 b);
    
};

#endif /* vec2_hpp */
