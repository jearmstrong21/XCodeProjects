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
    bool plane::intersect(ray ray,float&t,surface_data&sd,pt::obj*out_o)const{
        sd.normal=n;
        out_o=(pt::obj*)this;

        ray.pos-=p0;

        t= -vec3::dot(ray.pos,n)/vec3::dot(ray.dir,n);
        
        vec3 end=ray.pos+t*ray.dir;
        //https://stackoverflow.com/a/18664150/9609025
        vec3 b1=vec3::normalize(vec3(n.y,-n.x,0));
        vec3 b2=vec3::cross(b1,n);

        float c1=vec3::dot(b1,end);
        float c2=vec3::dot(b2,end);
        
        sd.uv=vec2(c1,c2);
        
        return t>=0;
//
//        return -ray.pos.y/ray.dir.y;
    }
}
