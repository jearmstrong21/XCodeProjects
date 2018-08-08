//
//  mat3.cpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/3/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "mat3.hpp"

// [ col1.x col2.x col3.x ]   [ v.x ]
// [ col1.y col2.y col3.y ] * [ v.y ]
// [ col1.z col2.z col3.z ]   [ v.z ]

// [ 1.x 2.x 3.x ]   [ 4.x 5.x 6.x ]   [ r1 dot o.c1 r1 dot
// [ 1.y 2.y 3.y ] * [ 4.y 5.y 6.y ] = [ r2 dot o.c1
// [ 1.z 2.z 3.z ]   [ 4.z 5.z 6.z ]   [ r3 dot o.c1

namespace math{
    mat3::mat3(){
        col1=vec3(1,0,0);
        col2=vec3(0,1,0);
        col3=vec3(0,0,1);
    }
    
    mat3::mat3(vec3 c1,vec3 c2,vec3 c3){
        col1=c1;
        col2=c2;
        col3=c3;
    }
    
    vec3 mat3::row1(){
        return vec3(col1.x,col2.x,col3.x);
    }
    
    vec3 mat3::row2(){
        return vec3(col1.y,col2.y,col3.y);
    }
    
    vec3 mat3::row3(){
        return vec3(col1.z,col2.z,col3.z);
    }
    
    vec3 mat3::operator*(vec3 &other){
        return vec3(  vec3::dot(row1(), other),  vec3::dot(row2(), other),  vec3::dot(row3(), other)   );
    }
    
    mat3 mat3::operator*(mat3 &other){
        vec3 c1=vec3(  vec3::dot(row1(), other.col1),  vec3::dot(row2(), other.col1), vec3::dot(row1(), other.col1)  );
        vec3 c2=vec3(  vec3::dot(row1(), other.col2),  vec3::dot(row2(), other.col2), vec3::dot(row1(), other.col2)  );
        vec3 c3=vec3(  vec3::dot(row1(), other.col3),  vec3::dot(row2(), other.col3), vec3::dot(row1(), other.col3)  );
        return mat3(c1,c2,c3);
    }
    
    mat3 mat3::transpose(){
        return mat3(row1(), row2(), row3());
    }
}
