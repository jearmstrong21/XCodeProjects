//
//  main.cpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/3/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "ppm_image.hpp"

#include "vec3.hpp"
#include "vec2.hpp"
#include "mat3.hpp"
#include "utils.hpp"

#include "sdf_object.hpp"
#include "sdf_sphere.hpp"
#include "sdf_cube.hpp"

using sdf::sdf_object;
using sdf::sdf_sphere;
using sdf::sdf_cube;

using math::vec2;
using math::vec3;
using math::mat3;

const float EPSILON=0.0001;

sdf_sphere sphere;
sdf_cube cube;

float cubeSDF(vec3 p) {
    // If d.x < 0, then -1 < p.x < 1, and same logic applies to p.y, p.z
    // So if all components of d are negative, then p is inside the unit cube
    vec3 d = vec3::abs(p) - vec3(1.0, 1.0, 1.0);
    
    // Assuming p is inside the cube, how far is it from the surface?
    // Result will be negative or zero.
    float insideDistance = math::min(math::max(d.x, math::max(d.y, d.z)), 0.0);
    
    // Assuming p is outside the cube, how far is it from the surface?
    // Result will be positive or zero.
    float outsideDistance = vec3::length(vec3( math::max(d.x,0),math::max(d.y,0),math::max(d.z,0)  ));
    
    return insideDistance + outsideDistance;
}

float floorSDF(vec3 p){
    return p.y;
}

float sceneSDF(vec3 p){
    return math::min(floorSDF(p),math::min(cube.get_distance(p),sphere.get_distance(p)));
}

vec3 estimateNormal(vec3 p) {
    return vec3::normalize(vec3(
                          sceneSDF(vec3(p.x + EPSILON, p.y, p.z)) - sceneSDF(vec3(p.x - EPSILON, p.y, p.z)),
                          sceneSDF(vec3(p.x, p.y + EPSILON, p.z)) - sceneSDF(vec3(p.x, p.y - EPSILON, p.z)),
                          sceneSDF(vec3(p.x, p.y, p.z  + EPSILON)) - sceneSDF(vec3(p.x, p.y, p.z - EPSILON))
                          ));
}

struct raytrace_result{
    vec3 end;
    vec3 start;
    vec3 dir;
    float totalDist;
    float lastDist;
    int iters;
};

raytrace_result sdfTrace(ray ray){
    raytrace_result result;
    result.start=ray.pos;
    result.dir=ray.dir;
    result.totalDist=0;
    result.iters=0;
    for(int i=0;i<500;i++){
        result.iters++;
        float sdf=sceneSDF(ray.pos);
        result.totalDist+=sdf;
        result.lastDist=sdf;
        ray.pos+=sdf*ray.dir;
        result.end=ray.pos;
        if(sdf<EPSILON)return result;
    }
    return result;
}

int main(int argc, const char * argv[]) {
    ppm_image img;
    img.set_size(200, 200);
    img.alloc_mem();
    
    
    printf("Starting loop\n");
    
    vec2 resolution=vec2(img.get_w(),img.get_h());
    float aspect=resolution.x/resolution.y;
    
    vec3 camPos=vec3(2,1,2);
    vec3 lookAt=vec3(0,1,0);
    
    vec3 lightPos=vec3(2,3,2);
    
    sphere.pos=vec3(0,1,0);
    sphere.size=1;
    
    cube.pos=vec3(0,2,0);
    cube.size=1;
    
    float zoom=1;
    
    for(int x=0;x<img.get_w();x++){
        for(int y=0;y<img.get_h();y++){
            
            vec2 uv=vec2(x,img.get_h()-y)/resolution;
            uv-=0.5;
            uv.x*=aspect;
            
            ray camRay=cam_ray(uv, camPos, lookAt, zoom);
            
            raytrace_result trace1=sdfTrace(camRay);
            
            vec3 color=vec3(0.2,0,0);
            
            if(trace1.lastDist<EPSILON){
                vec3 n=vec3::normalize(estimateNormal(trace1.end));
                vec3 s=vec3::normalize(lightPos-trace1.end);
                float dotSN=vec3::dot(s, n);
                dotSN=math::clamp(dotSN, 0, 1);
                color=vec3(1,1,0)*dotSN;
            }
            
            ray shadowRay;
            shadowRay.pos=lightPos;
            shadowRay.dir=vec3::normalize(trace1.end-lightPos);
            raytrace_result trace2=sdfTrace(shadowRay);
            if(vec3::length(trace1.end-trace2.end)>sqrt(EPSILON)){
                color*=0.75;
            }
//            float f=((float)trace1.iters)/100.0;
//            color=vec3(f,f,f);
            
            img.set_pixel(x,y,  color.x,color.y,color.z);
            
        }
    }
    
    printf("Finished computation\n");
    
    img.save("raytracing-1.ppm");
    
    printf("Saved to disk\n");
    
    return 0;
}
