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

using math::complex;
using math::vec2;

float scene(vec3 p){
    return vec3::length(p-vec3(1,1,1))-0.2;
}

int main(int argc, const char * argv[]) {
    ppm_image img;
    img.set_size(100, 100);
    img.alloc_mem();


    printf("Starting loop\n");

    vec3 camPos=vec3(3,3,3);
    vec3 camLookAt=vec3(0,0,0);

    for(int x=0;x<img.get_w();x++){
        for(int y=0;y<img.get_h();y++){
            img.set_pixel(x,y, 0,0,0 );
            vec2 uv=vec2(x,img.get_h()-y)/vec2(img.get_w(),img.get_h());
            uv-=0.5;
//            uv.x*=img.get_w()/img.get_h();
            sdf::ray camRay=sdf::createCamera(uv, camPos, camLookAt, 1);

            vec3 pos=camRay.pos;
            vec3 dir=camRay.dir;
            bool done=false;
            for(int i=0;i<50&&!done;i++){
                float dist=vec3::length(pos-vec3(1,1,1))-0.2;
                pos+=dir*dist;
                if(dist<0.001){
                    done=true;
                    vec3 normal=sdf::estimateNormal(scene,pos);
                    normal*=0.5;
                    normal+=0.5;
                    img.set_pixel(x,y,  normal );
                }
            }
        }
    }

    printf("Finished computation\n");

    img.save("result-1.ppm");

    printf("Saved to disk\n");

    return 0;
}
