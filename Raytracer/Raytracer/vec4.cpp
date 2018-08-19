//
//  vec4.cpp
//  Raytracer
//
//  Created by Jack Armstrong on 8/14/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "vec4.hpp"

namespace math{
    
    vec4::vec4(){
        this->x=0;
        this->y=0;
        this->z=0;
        this->w=0;
    }
    
    vec4::vec4(float xyzw){
        this->x=xyzw;
        this->y=xyzw;
        this->z=xyzw;
        this->w=xyzw;
    }
    
    vec4::vec4(float x,float y,float z,float w){
        this->x=x;
        this->y=y;
        this->z=z;
        this->w=w;
    }
    
    float vec4::length(vec4 v){
        return sqrt(v.x*v.x+v.y*v.y+v.z*v.z+v.w*v.w);
    }
    
    float vec4::dot(vec4 a,vec4 b){
        return a.x*b.x+a.y*b.y+a.z*b.z+a.w*b.w;
    }
    
    vec4 vec4::normalize(vec4 v){
        return v/length(v);
    }
    
    vec4& vec4::operator += (const vec4 rhs){
        x+=rhs.x;
        y+=rhs.y;
        z+=rhs.z;
        w+=rhs.w;
        return *this;
    }
    
    vec4& vec4::operator -= (const vec4 rhs){
        x-=rhs.x;
        y-=rhs.y;
        z-=rhs.z;
        w-=rhs.w;
        return *this;
    }
    
    vec4& vec4::operator *= (const vec4 rhs){
        x*=rhs.x;
        y*=rhs.y;
        z*=rhs.z;
        w*=rhs.w;
        return *this;
    }
    
    vec4& vec4::operator /= (const vec4 rhs){
        x/=rhs.x;
        y/=rhs.y;
        z/=rhs.z;
        w/=rhs.w;
        return *this;
    }
    
    vec4& vec4::operator += (const float rhs){
        x+=rhs;
        y+=rhs;
        z+=rhs;
        w+=rhs;
        return *this;
    }
    
    vec4& vec4::operator -= (const float rhs){
        x-=rhs;
        y-=rhs;
        z-=rhs;
        w-=rhs;
        return *this;
    }
    
    vec4& vec4::operator *= (const float rhs){
        x*=rhs;
        y*=rhs;
        z*=rhs;
        w*=rhs;
        return *this;
    }
    
    vec4& vec4::operator /= (const float rhs){
        x/=rhs;
        y/=rhs;
        z/=rhs;
        w/=rhs;
        return *this;
    }
    
    vec4 operator + (vec4 a, vec4 b){
        return vec4(a.x+b.x,a.y+b.y,a.z+b.z,a.w+b.w);
    }
    
    vec4 operator - (vec4 a,vec4 b){
        return vec4(a.x-b.x,a.y-b.y,a.z-b.z,a.w-b.w);
    }
    
    vec4 operator * (vec4 a,vec4 b){
        return vec4(a.x*b.x,a.y*b.y,a.z*b.z,a.w*b.w);
    }
    
    vec4 operator / (vec4 a,vec4 b){
        return vec4(a.x/b.x,a.y/b.y,a.z/b.z,a.w/b.w);
    }
    
    vec4 operator + (vec4 a,float b){
        return vec4(a.x+b,a.y+b,a.z+b,a.w+b);
    }
    
    vec4 operator - (vec4 a,float b){
        return vec4(a.x-b,a.y-b,a.z-b,a.w-b);
    }
    
    vec4 operator * (vec4 a,float b){
        return vec4(a.x*b,a.y*b,a.z*b,a.w*b);
    }
    vec4 operator / (vec4 a,float b){
        return vec4(a.x/b,a.y/b,a.z/b,a.w/b);
    }
    
    vec4 operator + (float a,vec4 b){
        return vec4(a+b.x,a+b.y,a+b.z,a+b.w);
    }
    
    vec4 operator - (float a,vec4 b){
        return vec4(a-b.x,a-b.y,a-b.z,a-b.w);
    }
    
    vec4 operator * (float a,vec4 b){
        return vec4(a*b.x,a*b.y,a*b.z,a*b.w);
    }
    
    vec4 operator / (float a,vec4 b){
        return vec4(a/b.x,a/b.y,a/b.z,a/b.w);
    }
    
}
