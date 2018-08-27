//
//  main.cpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/3/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "ppm_image.hpp"

#include "math/complex.hpp"
#include "math/vec2.hpp"

#include "rm.hpp"
#include "rm_modular.hpp"

//#include "sdf.hpp"
//#include "sdf_utils.hpp"
//#include "sdf_shapes.hpp"
//#include "sdf_config.hpp"

//#include "scene_infinite_spheres.hpp"
//#define scene scene_infinite_spheres

using math::complex;
using math::vec2;
using math::vec3;

rm::modular* scene_obj;

float scene(vec3 p){
//    vec3 mp=p;
//    mp.x=fmod(mp.x,1)-0.5;
//    mp.y=fmod(mp.y,3)-1.5;
//    mp.z=fmod(mp.z,1)-0.5;
//    if(p.y<0.5)mp.y=-10;
//    return math::min(math::min(math::min(p.x,p.y),p.z),vec3::length(mp)-0.3);
    return scene_obj->distance(p);
}
vec3 cam_pos=vec3(5,2,4);
vec3 look_at=vec3(0,0,0);
vec3 light_pos=vec3(2,3,2);

void get_color(vec3 pos, float& main_dist, vec3& cam_dir, vec3& ray_end, vec3& normal, vec3& result){
    main_dist=rm::trace_scene(scene, pos, cam_dir, RM_EPSILON, 1000);
    
    ray_end=pos+cam_dir*main_dist;
    
    normal=rm::estimate_normal(scene, ray_end);
    
    result=0.5+0.5*normal;
//    result=vec3(1);
    
    vec3 l=vec3::normalize(light_pos-ray_end);
    float diffuse=vec3::dot(l,normal);
//    vec3 r=2*vec3::dot(l,normal)*normal-l;
    vec3 r=vec3::reflect(l,normal);
    vec3 v=vec3::normalize(pos-ray_end);
    float specular=pow(vec3::dot(r,v),20);
    
    float shadow=math::lin_remap(rm::shadow_res(scene, ray_end, light_pos, RM_EPSILON),0,1,   0.5,1);
    
    result*=diffuse+specular;
    result*=shadow;
}

void final_color(vec3 &result,int x,int y,int w,int h){
    vec2 coord=vec2(x,y);
    vec2 uv=coord/vec2(w,h);
    uv-=0.5;
    uv.x*=w/h;
    
    float main_dist;
    vec3 cam_dir=rm::cam_dir(uv, cam_pos, look_at, 1);
    vec3 ray_end;
    vec3 normal;
    result=vec3(0);
    
    get_color(cam_pos, main_dist,cam_dir,ray_end,normal,result);
    float reflect_mult=0.25;
    for(int i=0;i<0;i++){
        float sec_dist;
        vec3 sec_cam_dir=vec3::reflect(vec3::normalize(cam_pos-ray_end),normal);
        vec3 sec_ray_end;
        vec3 sec_normal;
        vec3 sec_result;
        
        get_color(ray_end, sec_dist, sec_cam_dir, sec_ray_end, sec_normal, sec_result);
        
        result*=1-reflect_mult;
        result+=reflect_mult*sec_result;
        reflect_mult*=0.2;
        
        main_dist=sec_dist;
        cam_dir=sec_cam_dir;
        ray_end=sec_ray_end;
        normal=sec_normal;
    }
}

int main(int argc, const char * argv[]) {
    ppm_image img;
    img.set_size(300, 300);
    img.alloc_mem();

    printf("Starting loop\n");

    
    scene_obj=new rm::min(new rm::plane(vec3(0),vec3(0,1,0)), new rm::sphere(vec3(1),1)   );
    
    for(int x=0;x<img.get_w();x++){
        for(int y=0;y<img.get_h();y++){
            vec3 result;
            final_color(result, x,y, img.get_w(),img.get_h());
            img.set_pixel(x,y,  result );
            
//            img.set_pixel(x,y,result);
           
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
    img.dealloc();

    printf("Saved to disk\n");

    return 0;
}
