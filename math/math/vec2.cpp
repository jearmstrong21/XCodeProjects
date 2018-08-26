//
//  vec2.cpp
//  math
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
    
    vec2 vec2::normalize(vec2 v){
        return v/length(v);
    }
    
    vec2 vec2::abs(vec2 v){
        return vec2(math::abs(v.x),math::abs(v.y));
    }
    
    float vec2::dot2(vec2 a){
        return a.x*a.x+a.y*a.y;
    }
    
    float vec2::length8(vec2 v){
        v*=v;//^2
        v*=v;//^4
        v*=v;//^8
        return pow(v.x+v.y,0.125);//(v.x^8+v.y^8)^(1/8)
    }
    
    vec2 vec2::max(vec2 a,vec2 b){
        return vec2(math::max(a.x,b.x),math::max(a.y,b.y));
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
