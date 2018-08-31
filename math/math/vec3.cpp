//
//  vec3.cpp
//  math
//
//  Created by Jack Armstrong on 8/14/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "vec3.hpp"

namespace math{
    
    vec3::vec3(){
        this->x=0;
        this->y=0;
        this->z=0;
    }
    
    vec3::vec3(float xyz){
        this->x=xyz;
        this->y=xyz;
        this->z=xyz;
    }
    
    vec3::vec3(float x,float y,float z){
        this->x=x;
        this->y=y;
        this->z=z;
    }
    
    float vec3::dot2(vec3 v){
        return v.x*v.x+v.y*v.y+v.z*v.z;
    }
    
    vec3 vec3::sphere_coords(float theta,float phi){
        return vec3(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));
    }
    
    vec3 vec3::reflect(vec3 i,vec3 n){
        return 2*dot(n,i)*n-i;
    }
    
    vec3 vec3::max(vec3 a,vec3 b){
        return vec3(math::max(a.x,b.x),math::max(a.y,b.y),math::max(a.z,b.z));
    }
    
    vec3 vec3::min(vec3 a,vec3 b){
        return vec3(math::min(a.x,b.x),math::min(a.y,b.y),math::min(a.z,b.z));
    }
    
    vec3 vec3::abs(vec3 p){
        return vec3(math::abs(p.x),math::abs(p.y),math::abs(p.z));
    }
    
    float vec3::length(vec3 v){
        return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
    }
    
    float vec3::dot(vec3 a,vec3 b){
        return a.x*b.x+a.y*b.y+a.z*b.z;
    }
    
    vec3 vec3::cross(vec3 a,vec3 b){
        return vec3(a.y*b.z-a.z*b.y,a.x*b.z-a.z*b.x,a.x*b.y-a.y*b.x);
    }
    
    vec3 vec3::normalize(vec3 v){
        return v/length(v);
    }
    
    vec3& vec3::operator += (const vec3 rhs){
        x+=rhs.x;
        y+=rhs.y;
        z+=rhs.z;
        return *this;
    }
    
    vec3& vec3::operator -= (const vec3 rhs){
        x-=rhs.x;
        y-=rhs.y;
        z-=rhs.z;
        return *this;
    }
    
    vec3& vec3::operator *= (const vec3 rhs){
        x*=rhs.x;
        y*=rhs.y;
        z*=rhs.z;
        return *this;
    }
    
    vec3& vec3::operator /= (const vec3 rhs){
        x/=rhs.x;
        y/=rhs.y;
        z/=rhs.z;
        return *this;
    }
    
    vec3& vec3::operator += (const float rhs){
        x+=rhs;
        y+=rhs;
        z+=rhs;
        return *this;
    }
    
    vec3& vec3::operator -= (const float rhs){
        x-=rhs;
        y-=rhs;
        z-=rhs;
        return *this;
    }
    
    vec3& vec3::operator *= (const float rhs){
        x*=rhs;
        y*=rhs;
        z*=rhs;
        return *this;
    }
    
    vec3& vec3::operator /= (const float rhs){
        x/=rhs;
        y/=rhs;
        z/=rhs;
        return *this;
    }
    
    vec3 operator + (vec3 a, vec3 b){
        return vec3(a.x+b.x,a.y+b.y,a.z+b.z);
    }
    
    vec3 operator - (vec3 a,vec3 b){
        return vec3(a.x-b.x,a.y-b.y,a.z-b.z);
    }
    
    vec3 operator * (vec3 a,vec3 b){
        return vec3(a.x*b.x,a.y*b.y,a.z*b.z);
    }
    
    vec3 operator / (vec3 a,vec3 b){
        return vec3(a.x/b.x,a.y/b.y,a.z/b.z);
    }
    
    vec3 operator + (vec3 a,float b){
        return vec3(a.x+b,a.y+b,a.z+b);
    }
    
    vec3 operator - (vec3 a,float b){
        return vec3(a.x-b,a.y-b,a.z-b);
    }
    
    vec3 operator * (vec3 a,float b){
        return vec3(a.x*b,a.y*b,a.z*b);
    }
    vec3 operator / (vec3 a,float b){
        return vec3(a.x/b,a.y/b,a.z/b);
    }
    
    vec3 operator + (float a,vec3 b){
        return vec3(a+b.x,a+b.y,a+b.z);
    }
    
    vec3 operator - (float a,vec3 b){
        return vec3(a-b.x,a-b.y,a-b.z);
    }
    
    vec3 operator * (float a,vec3 b){
        return vec3(a*b.x,a*b.y,a*b.z);
    }
    
    vec3 operator / (float a,vec3 b){
        return vec3(a/b.x,a/b.y,a/b.z);
    }
    
}
