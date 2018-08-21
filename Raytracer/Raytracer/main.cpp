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
    vec3 modded=p;
    modded.x=fmod(p.x,1)-0.5;
    modded.y=fmod(p.y,1)-0.5;
    modded.z=fmod(p.z,1)-0.5;
    float content=vec3::length(p-vec3(5,2,3))-0.5;
    return math::min(walls, content);
}


vec3 camPos=vec3(6,3,3);
vec3 camLookAt=vec3(0);

vec3 lightPos=vec3(1);

float sceneDiffuse=0.4;
float sceneSpecular=0.4;
float sceneShininess=30;
float sceneReflect=0; //portion of reflect color that is mixed into current color
float sceneAmbient=1-sceneDiffuse-sceneSpecular;

vec3 shade(vec3 pos,vec3 eye,vec3 n, vec3 diffuse,vec3 specular,float shininess){
    
    vec3 s=-1*vec3::normalize(pos-lightPos);
    vec3 r=vec3::normalize(-1*s+2.0*vec3::dot(s,n)*n);
    vec3 v=vec3::normalize(eye-pos);
    
    vec3 lightDiffuse=diffuse*vec3::dot(s,n);
    vec3 f=vec3(0);
    float dotted=vec3::dot(r,v);
    vec3 lightSpecular=specular*pow(dotted,shininess);
    if(dotted<0.0)lightSpecular=vec3(0.0);
    
    f+=lightDiffuse;
    f+=lightSpecular;
    
    return f;
}

vec3 getColor(sdf::ray camera,int iters,sdf::trace& mainTrace){
    mainTrace=sdf::raymarch(scene, camera.pos, camera.dir);
    
    vec3 normal=sdf::estimateNormal(scene, mainTrace.end);
    
//    vec3 colNormal=0.5+0.5*normal;
    
    vec3 color=shade(mainTrace.end,camera.pos,normal,  vec3(sceneDiffuse),vec3(sceneSpecular),sceneShininess);
    
    sdf::trace shadowTrace=sdf::raymarch(scene, lightPos, vec3::normalize(mainTrace.end-lightPos));
    if(vec3::length(shadowTrace.end-mainTrace.end)>SQRT_EPSILON){
        color*=0.25;
//        color*=vec3(0.1*shadowTrace.min_d/shadowTrace.final_d);
    }
    color+=vec3(sceneAmbient);

//    if(sdf::sdSphere(mainTrace.end-vec3(2,0,2),0.5)<EPSILON&&iters<5){
    if(iters<4){
        sdf::trace reflection;
        vec3 c=getColor(sdf::ray(mainTrace.end+EPSILON*normal,normal),iters+1,reflection);
        color=color*(1-sceneReflect)+c*sceneReflect;
    }

    return color;
    
}

int main(int argc, const char * argv[]) {
    ppm_image img;
    img.set_size(500, 500);
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

            sdf::trace mainTrace;
            img.set_pixel(x,y, getColor(camera,0,mainTrace) );
           
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
