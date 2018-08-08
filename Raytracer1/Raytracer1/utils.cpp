//
//  utils.cpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/5/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "utils.hpp"

ray cam_ray(vec2 uv, vec3 camPos, vec3 lookAt, float zoom){
    vec3 f=vec3::normalize(lookAt-camPos);
    vec3 r=vec3::cross(vec3(0,1,0),f);
    vec3 u=vec3::cross(f,r);
    
    vec3 c=camPos+f*zoom;
    vec3 i=c+uv.x*r+uv.y*u;
    vec3 dir=i-camPos;
    ray ra;
    ra.pos=camPos;
    ra.dir=vec3::normalize(dir);
    return ra;
}

mat3 view_matrix(vec3 eye,vec3 center,vec3 up){
    vec3 f=vec3::normalize(center-eye);
    vec3 s=vec3::normalize(vec3::cross(f,up));
    vec3 u=vec3::cross(s,f);
    return mat3(s,u,-f);
}


namespace math{
    float max(float a,float b){
        return a>b?a:b;
    }
    
    float min(float a,float b){
        return a<b?a:b;
    }
    
    float norm(float t,float a,float b) {
        return (t-a)/(b-a);
    }
    
    float lerp(float t,float a,float b) {
        return a+t*(b-a);
    }
    
    
    float clamp(float t,float a,float b) {
        if(t<a)return a;
        if(t>b)return b;
        return t;
    }
    
    bool isInRange(float t,float a,float b) {
        return t==clamp(t,a,b);
    }
    
    float lin_remap(float t,float s1,float e1,float s2,float e2) {
        return lerp(norm(t,s1,e1),s2,e2);
    }
    
};

namespace color{
    
    float thetaToR(float theta) {//in range 0 to 1
        theta=round(fmod(theta,1)*360);
        if(math::isInRange(theta, 0, 60))return 1;
        if(math::isInRange(theta, 60, 120))return math::lin_remap(theta, 60, 120, 1, 0);
        if(math::isInRange(theta, 120, 180))return 0;
        if(math::isInRange(theta, 180, 240))return 0;
        if(math::isInRange(theta, 240, 300))return math::lin_remap(theta, 240, 300, 0, 1);
        if(math::isInRange(theta, 300, 360))return 0;
        return 0;
    }
    
    float thetaToG(float theta) {//in range 0 to 1
        theta=round(fmod(theta,1)*360);
        if(math::isInRange(theta, 0, 60))return math::lin_remap(theta, 0, 60, 0, 1);
        if(math::isInRange(theta, 60, 120))return 1;
        if(math::isInRange(theta, 120, 180))return 1;
        if(math::isInRange(theta, 180, 240))return math::lin_remap(theta, 180, 240, 1, 0);
        if(math::isInRange(theta, 240, 300))return 0;
        if(math::isInRange(theta, 300, 360))return 0;
        return 0;
    }
    
    float thetaToB(float theta) {//in range 0 to 1
        theta=round(fmod(theta,1)*360);
        if(math::isInRange(theta, 0, 60))return 0;
        if(math::isInRange(theta, 60, 120))return 0;
        if(math::isInRange(theta, 120, 180))return math::lin_remap(theta, 120, 180, 0, 1);
        if(math::isInRange(theta, 180, 240))return 1;
        if(math::isInRange(theta, 240, 300))return 1;
        if(math::isInRange(theta, 300, 360))return math::lin_remap(theta, 300, 360, 1, 0);
        return 0;
    }

};
