//
//  pt_plane.cpp
//  Pathtracer
//
//  Created by Jack Armstrong on 8/26/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "pt_plane.hpp"

namespace pt{
    plane::plane(){
        n=vec3(0);
        p0=vec3(0);
    }
    plane::plane(vec3 n,vec3 p0){
        this->n=n;
        this->p0=p0;
    }
    plane::~plane(){
        
    }
    bool plane::intersect(ray ray,float&t,vec3&out_n,pt::obj*out_o)const{
        out_n=n;
        out_o=(pt::obj*)this;

        ray.pos-=p0;

        t= -vec3::dot(ray.pos,n)/vec3::dot(ray.dir,n);
        return t>=0;
//
//        return -ray.pos.y/ray.dir.y;
    }
}
