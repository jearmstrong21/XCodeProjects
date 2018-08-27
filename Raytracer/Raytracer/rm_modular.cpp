//
//  rm_modular.cpp
//  Raytracer
//
//  Created by Jack Armstrong on 8/27/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "rm_modular.hpp"

namespace rm {
    
//    namespace modular {
    
    min::min(modular*a,modular*b){
        this->a=a;
        this->b=b;
    }
    
    sphere::sphere(vec3 p,float s){
        pos=p;
        size=s;
    }
    
    plane::plane(vec3 p,vec3 n){
        pos=p;
        normal=n;
    }
    
    float min::distance(vec3 pos)const{
        return math::min(a->distance(pos),b->distance(pos));
    }
    
    float sphere::distance(vec3 pos)const{
        return vec3::length(pos-this->pos)-size;
    }
    
    float plane::distance(vec3 pos)const{
        return vec3::dot(pos-this->pos,normal);
    }
    
//    }
    
}
