//
//  main.cpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/3/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "ppm_image.hpp"

#include "complex.hpp"
#include "vec2.hpp"
#include "hsv.hpp"

#include "sdf.hpp"
#include "sdf_utils.hpp"
#include "sdf_shapes.hpp"
#include "sdf_config.hpp"

using math::complex;
using math::vec2;

float scene(vec3 p){
    float walls=math::min(sdf::sdPlane(p,vec4(1,0,0,0)),math::min(sdf::sdPlane(p,vec4(0,1,0,0)),sdf::sdPlane(p,vec4(0,0,1,0))));
    return math::min(sdf::sdBox(p-vec3(2,0,2),0.5), walls);
}


vec3 camPos=vec3(7,3,4);
vec3 camLookAt=vec3(0);

vec3 lightPos=vec3(1);

vec3 getColor(sdf::ray camera,int iters){
    sdf::trace mainTrace=sdf::raymarch(scene, camera.pos, camera.dir);
    
    vec3 normal=sdf::estimateNormal(scene, mainTrace.end);
    
    float dotSN=math::clamp(vec3::dot(normal,vec3::normalize(lightPos-mainTrace.end)), 0, 1);
    
    vec3 colNormal=0.5+0.5*normal;
    
    vec3 color=colNormal;
    color*=dotSN;
    
    sdf::trace shadowTrace=sdf::raymarch(scene, lightPos, vec3::normalize(mainTrace.end-lightPos));
    if(vec3::length(shadowTrace.end-mainTrace.end)>SQRT_EPSILON){
        color*=0.25;
    }

//    if(sdf::sdBox(mainTrace.end-vec3(2,0,2),0.5)<EPSILON&&iters<5){
//        color*=0.5;
//        color+=0.5*getColor(sdf::ray(mainTrace.end,normal),iters+1);
//    }
    
    return color;
    
}

int main(int argc, const char * argv[]) {
    ppm_image img;
    img.set_size(1000, 1000);
    img.alloc_mem();


    printf("Starting loop\n");

    for(int x=0;x<img.get_w();x++){
        for(int y=0;y<img.get_h();y++){
            img.set_pixel(x,y, 0,0,0 );
            
            vec2 coord=vec2(x,y);
            vec2 uv=coord/vec2(img.get_w(),img.get_h());
            uv-=0.5;
            uv.x*=img.get_w()/img.get_h();
            
            sdf::ray camera=sdf::createCamera(uv, camPos, camLookAt, 1);

            img.set_pixel(x,y, getColor(camera,0) );
           
//            img.set_pixel(x,y,  coord.x/img.get_w(),coord.y/img.get_h(),0);
        }
        if(x % (img.get_w()/100) == 0){
            float percentage=100.0*x/img.get_w();
            printf("Percentage: %i%%\n",(int)percentage);
        }
    }

    printf("Finished computation\n");

    img.clamp();
    img.save("result-1.ppm");

    printf("Saved to disk\n");

    return 0;
}
