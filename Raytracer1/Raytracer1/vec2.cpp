//
//  vec2.cpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/5/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "vec2.hpp"

namespace math{

    vec2::vec2(){
        x=0;
        y=0;
    }
    vec2::vec2(float x,float y){
        this->x=x;
        this->y=y;
    }
    vec2::vec2(const vec2 &other){
        this->x=other.x;
        this->y=other.y;
    }
    
    vec2 vec2::operator + (vec2 &other){
        return vec2(x+other.x,y+other.y);
    }
    vec2 vec2::operator - (vec2 &other){
        return vec2(x-other.x,y-other.y);
    }
    vec2 vec2::operator * (vec2 &other){
        return vec2(x*other.x,y*other.y);
    }
    vec2 vec2::operator / (vec2 &other){
        return vec2(x/other.x,y/other.y);
    }
    
    vec2 vec2::operator * (float other){
        return vec2(x*other,y*other);
    }
    vec2 vec2::operator / (float other){
        return vec2(x/other,y/other);
    }
    
    vec2& vec2::operator += (const vec2& rhs){
        x+=rhs.x;
        y+=rhs.y;
        return *this;
    }
    vec2& vec2::operator -= (const vec2& rhs){
        x-=rhs.x;
        y-=rhs.y;
        return *this;
    }
    vec2& vec2::operator *= (const vec2& rhs){
        x*=rhs.x;
        y*=rhs.y;
        return *this;
    }
    vec2& vec2::operator /= (const vec2& rhs){
        x/=rhs.x;
        y/=rhs.y;
        return *this;
    }
    
    vec2& vec2::operator += (const float& rhs){
        x+=rhs;
        y+=rhs;
        return *this;
    }
    vec2& vec2::operator -= (const float& rhs){
        x-=rhs;
        y-=rhs;
        return *this;
    }
    vec2& vec2::operator *= (const float& rhs){
        x*=rhs;
        y*=rhs;
        return *this;
    }
    vec2& vec2::operator /= (const float& rhs){
        x/=rhs;
        y/=rhs;
        return *this;
    }
    
    vec2 vec2::operator - (void) {
        return vec2(-x,-y);
    }
    
    float vec2::dot(vec2 a, vec2 b){
        return a.x*b.x+a.y*b.y;
    }
    
    float vec2::length(){
        return sqrt(x*x+y*y);
    }
    
    vec2 vec2::normalize(){
        float l=length();
        return vec2(x/l,y/l);
    }
    
    vec2 operator * (float a,vec2 b){
        return b*a;
    }
    
};
