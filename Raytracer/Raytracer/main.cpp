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

#include "rm.hpp"

//#include "sdf.hpp"
//#include "sdf_utils.hpp"
//#include "sdf_shapes.hpp"
//#include "sdf_config.hpp"

//#include "scene_infinite_spheres.hpp"
//#define scene scene_infinite_spheres

using math::complex;
using math::vec2;
using math::vec3;

float scene(vec3 p){
    vec3 mp=p;
    mp.x=fmod(mp.x,1)-0.5;
    mp.y=fmod(mp.y,3)-1.5;
    mp.z=fmod(mp.z,1)-0.5;
    if(p.y<0.5)mp.y=-10;
    return math::min(math::min(math::min(p.x,p.y),p.z),vec3::length(mp)-0.3);
}
vec3 cam_pos=vec3(5,3,4);
vec3 look_at=vec3(0,0,0);
vec3 light_pos=vec3(2,3,2);

void get_color(vec3 pos, float& main_dist, vec3& cam_dir, vec3& ray_end, vec3& normal, vec3& result){
    main_dist=rm::trace_scene(scene, pos, cam_dir, RM_EPSILON, 100);
    
    ray_end=pos+cam_dir*main_dist;
    
    normal=rm::estimate_normal(scene, ray_end);
    
    result=0.5+0.5*normal;
    
    vec3 l=vec3::normalize(light_pos-ray_end);
    float diffuse=vec3::dot(l,normal);
    vec3 r=2*vec3::dot(l,normal)*normal-l;
    vec3 v=vec3::normalize(pos-ray_end);
    float specular=pow(vec3::dot(r,v),20);
    
    float shadow=rm::shadow_res(scene, ray_end, light_pos, RM_EPSILON);
    
    result*=diffuse+specular;
    result*=shadow;
}

int main(int argc, const char * argv[]) {
    ppm_image img;
    img.set_size(10000, 10000);
    img.alloc_mem();

    printf("Starting loop\n");

    
    for(int x=0;x<img.get_w();x++){
        for(int y=0;y<img.get_h();y++){
            img.set_pixel(x,y, 0,0,0 );
            
            vec2 coord=vec2(x,y);
            vec2 uv=coord/vec2(img.get_w(),img.get_h());
            uv-=0.5;
            uv.x*=img.get_w()/img.get_h();
            
            float main_dist;
            vec3 cam_dir=rm::cam_dir(uv, cam_pos, look_at, 1);
            vec3 ray_end;
            vec3 normal;
            vec3 result;
            
            get_color(cam_pos, main_dist,cam_dir,ray_end,normal,result);
            for(int i=0;i<3;i++){
                float sec_dist;
                vec3 sec_cam_dir=normal;
                vec3 sec_ray_end;
                vec3 sec_normal;
                vec3 sec_result;

                get_color(ray_end, sec_dist, sec_cam_dir, sec_ray_end, sec_normal, sec_result);
                float reflect=0.25;
                result*=1-reflect;
                result+=reflect*sec_result;
                
                main_dist=sec_dist;
                cam_dir=sec_cam_dir;
                ray_end=sec_ray_end;
                normal=sec_normal;
            }
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

    printf("Saved to disk\n");

    return 0;
}
