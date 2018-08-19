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

int main(int argc, const char * argv[]) {
    ppm_image img;
    img.set_size(500, 500);
    img.alloc_mem();


    printf("Starting loop\n");

    vec3 camPos=vec3(7,3,4);
    vec3 camLookAt=vec3(0);
    
    vec3 lightPos=vec3(1);

    for(int x=0;x<img.get_w();x++){
        for(int y=0;y<img.get_h();y++){
            img.set_pixel(x,y, 0,0,0 );
            vec2 coord=vec2(x,y);
            vec2 uv=coord/vec2(img.get_w(),img.get_h());
            uv-=0.5;
            uv.x*=img.get_w()/img.get_h();
            sdf::ray camera=sdf::createCamera(uv, camPos, camLookAt, 1);
            
            sdf::trace mainTrace=sdf::raymarch(scene, camera.pos, camera.dir);
            
            vec3 normal=sdf::estimateNormal(scene, mainTrace.end);
            
            float dotSN=vec3::dot(normal,vec3::normalize(lightPos-mainTrace.end));
            
            vec3 colNormal=0.5+0.5*normal;

            vec3 color=colNormal;
            color*=dotSN;

            sdf::trace shadowTrace=sdf::raymarch(scene, mainTrace.end,lightPos-mainTrace.end);
            if(vec3::length(shadowTrace.end-mainTrace.end)>SQRT_EPSILON){
                color*=0.75;
            }

            img.set_pixel(x,y, color );
           
//            img.set_pixel(x,y,  coord.x/img.get_w(),coord.y/img.get_h(),0);
        }
    }

    printf("Finished computation\n");

    img.clamp();
    img.save("result-1.ppm");

    printf("Saved to disk\n");

    return 0;
}
