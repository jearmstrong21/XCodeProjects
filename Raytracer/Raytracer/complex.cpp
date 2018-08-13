//
//  complex.cpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/12/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "complex.hpp"

namespace math{
    complex::complex(float r,float theta){
        this->r=r;
        this->theta=theta;
    }
    complex complex::to_polar(float x, float y){
        return complex(sqrt(x*x+y*y),atan2(y,x));
    }
    
    float complex::length(complex c){
        return c.r;
    }
    
    float complex::get_x(complex c){
        return c.r*cos(c.theta);
    }
    
    float complex::get_y(complex c){
        return c.r*sin(c.theta);
    }
    
    complex operator + (complex a, complex b){
        return complex::to_polar(complex::get_x(a)+complex::get_x(b),complex::get_y(a)+complex::get_y(b));
    }
    
    complex operator - (complex a, complex b){
        return complex::to_polar(complex::get_x(a)-complex::get_x(b),complex::get_y(a)-complex::get_y(b));
    }
    
    complex operator * (complex a, complex b){
        return complex(a.r*b.r,a.theta+b.theta);
    }
    
    complex operator / (complex a, complex b){
        return complex(a.r/b.r,a.theta-b.theta);
    }
    
    complex operator + (complex a, float b){
        return complex::to_polar(complex::get_x(a)+b,complex::get_y(a));
    }
    
    complex operator - (complex a, float b){
        return complex::to_polar(complex::get_x(a)-b,complex::get_y(a));
    }
    
    complex operator * (complex a, float b){
        return complex(a.r*b,a.theta);
    }
    
    complex operator / (complex a, float b){
        return complex(a.r/b,a.theta);
    }
    
    complex operator + (float a,complex b){
        return b+a;
    }
    
    complex operator - (float a,complex b){
        return b+(-a);
    }
    
    complex operator * (float a,complex b){
        return b*a;
    }
    
    complex operator / (float a,complex b){
        return complex(a/b.r,-b.theta);
    }

};
