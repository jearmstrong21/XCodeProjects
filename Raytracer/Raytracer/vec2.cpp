//
//  vec2.cpp
//  Raytracer
//
//  Created by Jack Armstrong on 8/12/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "vec2.hpp"

namespace math{
    vec2::vec2(float x,float y){
        this->x=x;
        this->y=y;
    }
    
    vec2::vec2(float xy){
        this->x=xy;
        this->y=xy;
    }
    
    vec2::vec2(){
        this->x=0;
        this->y=0;
    }

    float vec2::length(vec2 v){
        return sqrt(v.x*v.x+v.y*v.y);
    }
    
    vec2& vec2::operator += (const vec2 rhs){
        x+=rhs.x;
        y+=rhs.y;
        return *this;
    }
    
    vec2& vec2::operator -= (const vec2 rhs){
        x-=rhs.x;
        y-=rhs.y;
        return *this;
    }
    
    vec2& vec2::operator *= (const vec2 rhs){
        x*=rhs.x;
        y*=rhs.y;
        return *this;
    }
    
    vec2& vec2::operator /= (const vec2 rhs){
        x/=rhs.x;
        y/=rhs.y;
        return *this;
    }
    
    vec2& vec2::operator *= (const float rhs){
        x*=rhs;
        y*=rhs;
        return *this;
    }
    
    vec2& vec2::operator /= (const float rhs){
        x/=rhs;
        y/=rhs;
        return *this;
    }
    
    float vec2::dot(vec2 a,vec2 b){
        return a.x*b.x+a.y*b.y;
    }
    
    vec2 operator + (vec2 a,vec2 b){
        return vec2(a.x+b.x,a.y+b.y);
    }
    
    vec2 operator - (vec2 a,vec2 b){
        return vec2(a.x-b.x,a.y-b.y);
    }
    
    vec2 operator * (vec2 a,vec2 b){
        return vec2(a.x*b.x,a.y*b.y);
    }
    
    vec2 operator / (vec2 a,vec2 b){
        return vec2(a.x/b.x,a.y/b.y);
    }
    
    vec2 operator * (vec2 a,float b){
        return vec2(a.x*b,a.y*b);
    }
    
    vec2 operator / (vec2 a,float b){
        return vec2(a.x/b,a.y/b);
    }
    
    vec2 operator * (float a,vec2 b){
        return b*a;
    }
}
