//
//  vec4.hpp
//  math
//
//  Created by Jack Armstrong on 8/18/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef vec4_hpp
#define vec4_hpp

#include <cmath>

#define X_AXIS4 vec4(1,0,0,0)
#define Y_AXIS4 vec4(0,1,0,0)
#define Z_AXIS4 vec4(0,0,1,0)
#define W_AXIS4 vec4(0,0,0,1)
#define ORIGIN4 vec4(0)

namespace math{
    struct vec4{
        float x;
        float y;
        float z;
        float w;
        vec4();
        vec4(float xyzw);
        vec4(float x,float y,float z,float w);
        
        static float length(vec4 v);
        static float dot(vec4 a,vec4 b);
        static vec4 normalize(vec4 v);
        
        vec4& operator += (const vec4 rhs);
        vec4& operator -= (const vec4 rhs);
        vec4& operator *= (const vec4 rhs);
        vec4& operator /= (const vec4 rhs);
        
        vec4& operator += (const float rhs);
        vec4& operator -= (const float rhs);
        vec4& operator *= (const float rhs);
        vec4& operator /= (const float rhs);
    };
    
    vec4 operator + (vec4 a,vec4 b);
    vec4 operator - (vec4 a,vec4 b);
    vec4 operator * (vec4 a,vec4 b);
    vec4 operator / (vec4 a,vec4 b);
    
    vec4 operator + (vec4 a,float b);
    vec4 operator - (vec4 a,float b);
    vec4 operator * (vec4 a,float b);
    vec4 operator / (vec4 a,float b);
    
    vec4 operator + (float a,vec4 b);
    vec4 operator - (float a,vec4 b);
    vec4 operator * (float a,vec4 b);
    vec4 operator / (float a,vec4 b);
};

#endif /* vec4_hpp */
