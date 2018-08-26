//
//  complex.hpp
//  math
//
//  Created by Jack Armstrong on 8/12/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef complex_hpp
#define complex_hpp

#include <stdio.h>
#include <cmath>

namespace math{
    struct complex{
        float r;
        float theta;
        
        complex(float,float);
        
        static complex to_polar(float x,float y);
        static float get_x(complex c);
        static float get_y(complex c);
        static float length(complex c);
        
        complex& operator += (const complex rhs);
        complex& operator -= (const complex rhs);
        complex& operator *= (const complex rhs);
        complex& operator /= (const complex rhs);
        
        complex& operator += (const float rhs);
        complex& operator -= (const float rhs);
        complex& operator *= (const float rhs);
        complex& operator /= (const float rhs);
    };
    
    complex operator + (complex, complex);
    complex operator - (complex, complex);
    complex operator * (complex, complex);
    complex operator / (complex, complex);
    
    complex operator + (complex, float);
    complex operator - (complex, float);
    complex operator * (complex, float);
    complex operator / (complex, float);
    
    complex operator + (float, complex);
    complex operator - (float, complex);
    complex operator * (float, complex);
    complex operator / (float, complex);
    
    
    
};

#endif /* complex_hpp */
