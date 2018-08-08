//
//  vec3.cpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/3/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "vec3.hpp"

namespace math{
    
    vec3::vec3(){
        x=0;
        y=0;
        z=0;
    }
    
    vec3::vec3(float x,float y,float z){
        this->x=x;
        this->y=y;
        this->z=z;
    }
    
    vec3::vec3(const vec3 &other){
        x=other.x;
        y=other.y;
        z=other.z;
    }
    
    vec3 vec3::operator+(vec3 other){
        return vec3(x+other.x,y+other.y,z+other.z);
    }
    
    vec3 vec3::operator-(vec3 other){
        return vec3(x-other.x,y-other.y,z-other.z);
    }
    
    vec3 vec3::operator*(vec3 other){
        return vec3(x*other.x,y*other.y,z*other.z);
    }
    
    vec3 vec3::operator/(vec3 other){
        return vec3(x/other.x,y/other.y,z/other.z);
    }
    
    vec3 vec3::operator*(float other){
        return vec3(x*other,y*other,z*other);
    }
    
    vec3 vec3::operator/(float other){
        return vec3(x/other,y/other,z/other);
    }
    
    vec3 vec3::operator - (void) {
        return vec3(-x,-y,-z);
    }
    
    
    vec3& vec3::operator += (const vec3& rhs){
        x+=rhs.x;
        y+=rhs.y;
        z+=rhs.z;
        return *this;
    }
    vec3& vec3::operator -= (const vec3& rhs){
        x-=rhs.x;
        y-=rhs.y;
        z-=rhs.z;
        return *this;
    }
    vec3& vec3::operator *= (const vec3& rhs){
        x*=rhs.x;
        y*=rhs.y;
        z*=rhs.z;
        return *this;
    }
    vec3& vec3::operator /= (const vec3& rhs){
        x/=rhs.x;
        y/=rhs.y;
        z/=rhs.z;
        return *this;
    }
    
    
    vec3& vec3::operator += (const float& rhs){
        x+=rhs;
        y+=rhs;
        z+=rhs;
        return *this;
    }
    vec3& vec3::operator -= (const float& rhs){
        x-=rhs;
        y-=rhs;
        z-=rhs;
        return *this;
    }
    vec3& vec3::operator *= (const float& rhs){
        x*=rhs;
        y*=rhs;
        z*=rhs;
        return *this;
    }
    vec3& vec3::operator /= (const float& rhs){
        x/=rhs;
        y/=rhs;
        z/=rhs;
        return *this;
    }
    
    float vec3::dot(vec3 a, vec3 b){
        return a.x*b.x+a.y*b.y+a.z*b.z;
    }
    
    vec3 vec3::cross(vec3 a, vec3 b){
        return vec3(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
    }
    
    vec3 operator*(float a,vec3 b){
        return b*a;
    }
    
    float vec3::length(vec3 a){
        return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
    }
    
    vec3 vec3::normalize(vec3 a){
        return vec3(a.x,a.y,a.z)/length(a);
    }
    
    vec3 vec3::abs(vec3 a){
        float x=a.x;
        float y=a.y;
        float z=a.z;
        return vec3(x<0?-x:x,y<0?-y:y,z<0?-z:z);
    }
    
    vec3 vec3::max(vec3 a,vec3 b){
        return vec3(math::max(a.x,b.x),math::max(a.y,b.y),math::max(a.z,b.z));
    }
    
    vec3 vec3::max(vec3 a,float b){
        return vec3(math::max(a.x,b),math::max(a.y,b),math::max(a.z,b));
    }
    
    vec3 vec3::max(float a,vec3 b){
        return max(b,a);
    }

    vec3 vec3::mod(vec3 a,float b){
        while(a.x<0)a.x+=b;
        while(a.y<0)a.y+=b;
        while(a.z<0)a.z+=b;
        while(a.x>=b)a.x-=b;
        while(a.y>=b)a.y-=b;
        while(a.z>=b)a.z-=b;
        return a;
    }
    
    vec3 vec3::u_mod(vec3 a,float b){
        while(a.x<=-b)a.x+=b;
        while(a.y<=-b)a.y+=b;
        while(a.z<=-b)a.z+=b;
        while(a.x>=b)a.x-=b;
        while(a.y>=b)a.y-=b;
        while(a.z>=b)a.z-=b;
        return a;
    }
    
};
