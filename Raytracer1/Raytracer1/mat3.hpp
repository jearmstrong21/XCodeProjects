//
//  mat3.hpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/3/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef mat3_hpp
#define mat3_hpp

#include <stdio.h>
#include <cmath>

#include "vec3.hpp"

//col1.x col2.x col3.x
//col1.y col2.y col3.y
//col1.z col2.z col3.z

namespace math{
    
    class mat3{
    public:
        vec3 col1;
        vec3 col2;
        vec3 col3;
        
        mat3();
        mat3(vec3 c1,vec3 c2,vec3 c3);
        
        mat3 operator * (mat3 &other);
        vec3 operator * (vec3 &other);
        
        vec3 row1();
        vec3 row2();
        vec3 row3();
        
        mat3 transpose();
    };
};


#endif /* mat3_hpp */
