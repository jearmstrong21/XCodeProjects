//
//  complex2.hpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/3/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef complex2_hpp
#define complex2_hpp

#include <cmath>

namespace math{
    class complex2 {
    private:
        float r;
        float theta;
    public:
        complex2();
        complex2(float r,float theta);
        complex2(const complex2 &other);
        
        float x();
        float y();
        
        complex2 operator + (complex2 &other);
        complex2 operator - (complex2 &other);
        complex2 operator * (complex2 &other);
        complex2 operator / (complex2 &other);
        complex2 operator + (float other);
        complex2 operator - (float other);
        complex2 operator * (float other);
        complex2 operator / (float other);
        
        float length();
        float angle();
        
        static complex2 to_polar(float x,float y);
        static complex2 from_polar(float x,float y);
        
    };
    
    complex2 operator+(float a,complex2 b);
    complex2 operator-(float a,complex2 b);
    complex2 operator*(float a,complex2 b);
    complex2 operator/(float a,complex2 b);
    
    
    
};

#endif /* complex2_hpp */
