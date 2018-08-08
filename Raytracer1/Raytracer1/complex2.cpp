//
//  complex2.cpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/3/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "complex2.hpp"

namespace math{

    complex2::complex2(){
        r=0;
        theta=0;
    }
    
    complex2::complex2(float r,float theta){
        this->r=r;
        this->theta=theta;
    }
    
    complex2::complex2(const complex2 &other){
        r=other.r;
        theta=other.theta;
    }

    float complex2::angle(){
        return theta;
    }

    float complex2::length(){
        return r;
    }

    complex2 complex2::from_polar(float r, float theta){
        complex2 c;
        c.r=r;
        c.theta=theta;
        return c;
    }
    
    complex2 complex2::to_polar(float x, float y){
        return from_polar(sqrt(x*x+y*y), atan2(y, x));
    }
    
    complex2 complex2::operator+(complex2 &other){
        return to_polar(x()+other.x(),y()+other.y());
    }
    
    complex2 complex2::operator-(complex2 &other){
        return to_polar(x()-other.x(),y()-other.y());
    }
    complex2 complex2::operator*(complex2 &other){
        return from_polar(r*other.r, theta+other.theta);
    }
    
    complex2 complex2::operator/(complex2 &other){
        return from_polar(r/other.r, theta-other.theta);
    }
    
    complex2 complex2::operator+(float other){
        return to_polar(x()+other,y());
    }
    
    complex2 complex2::operator-(float other){
        return to_polar(x()-other, y());
    }
    
    complex2 complex2::operator*(float other){
        return from_polar(r*other,theta);
    }
    
    complex2 complex2::operator/(float other){
        return from_polar(r/other,theta);
    }
    
    float complex2::x(){
        return cos(theta)*r;
    }
    
    float complex2::y(){
        return sin(theta)*r;
    }

    complex2 operator+(float a,complex2 b){
        return b+a;
    }
    
    complex2 operator-(float a,complex2 b){
        return (-1*b)+a;
    }
    
    complex2 operator*(float a,complex2 b){
        return b*a;
    }
    
    complex2 operator/(float a,complex2 b){
        return complex2::from_polar(a/b.length(), -b.angle());
    }
    
}
