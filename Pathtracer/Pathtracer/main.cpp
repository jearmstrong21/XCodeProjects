
#include "ppm_image.hpp"

#include "pt.hpp"

#include "pt_obj.hpp"
#include "pt_sphere.hpp"
#include "pt_list.hpp"
#include "pt_plane.hpp"
#include "pt_aabb.hpp"

#include "vec3.hpp"
#include "vec2.hpp"


using math::vec3;
using math::vec2;

const vec3 camPos=vec3(7,1,6);
const vec3 lookAt=vec3(0);

ppm_image zoe;

pt::list*list;
pt::plane*ground;
pt::sphere *sp;


float rand_1(){
    return (rand()%1000)/1000.0;
}

void final_color(pt::ray cam_ray,vec3& result){
    result=vec3(0);
    
    
//    pt::ray cam_ray=pt::cam_ray(uv, camPos, lookAt, 1);
    
    float t=0;
    pt::surface_data sd;
    pt::obj *o=NULL;
    bool intersection_found = list->intersect(cam_ray, t, sd, o);
    if(!intersection_found)return;
    
    vec3 ray_end=cam_ray.pos+cam_ray.dir*t;
    
    result=vec3(0.5+0.5*sd.normal);
//    int u_i=round(math::abs(sd.uv.x)*4);
//    int v_i=round(math::abs(sd.uv.y)*4);
//    result=vec3( 0.3+0.3*((u_i+v_i)%2)   );
//    result=vec3( 0.3+0.3*((u_i+v_i)%2)   )*(0.5+0.5*sd.normal);
//    result=vec3(math::abs(fmod(sd.uv.x,1)),math::abs(fmod(sd.uv.y,1)),0);
//    result=zoe.get_pixel(vec2(fmod(sd.uv.x,1),fmod(sd.uv.y,1)));
    
    vec3 n0=sd.normal;
    vec3 light_pos=vec3(6,1.5,7);
    vec3 d=vec3::normalize(light_pos-ray_end);
    bool in_shadow=list->intersect(pt::ray(ray_end+d*1e-1,d),  t,sd,o);
    if(in_shadow&&t<vec3::length(ray_end-light_pos))result*=0.25;
    result*=math::clamp(vec3::dot(n0,vec3::normalize(light_pos-ray_end)),0,1);
    
    float num_hits=0;
    float total=0;
    for(int i=0;i<100;i++){
        float occ_t;
        pt::surface_data occ_sd;
        pt::obj*occ_o=NULL;
        vec3 d=vec3::normalize(vec3(rand_1(),rand_1(),rand_1())*2-1);
        pt::ray r=pt::ray(ray_end+d*0.001, d  );
        bool b=list->intersect(r,occ_t,occ_sd,occ_o);
//        if(b&&occ_t<0.2){
//            num_hits++;
//        }
        if(b){
            num_hits+=1.0/(occ_t+1);
        }
        total++;
    }
//    float diff_t=TWO_PI/3;
//    float diff_p=TWO_PI/3;
//    for(float theta=0;theta<TWO_PI;theta+=diff_t){
//        for(float phi=0;phi<TWO_PI;phi+=diff_p){
//            float occ_t;
//            pt::surface_data occ_sd;
//            pt::obj*occ_o=NULL;
//            vec3 d=vec3::sphere_coords(theta,phi);
//            pt::ray r=pt::ray(ray_end+d*0.001, d);
//            bool b=list->intersect(r,occ_t,occ_sd,occ_o);
//            if(b&&occ_t<0.2){
//                num_hits++;
//            }
//            total++;
//        }
//    }
    //occlusion should be a function of pt::obj
    float occ=num_hits/total;
    result=vec3(1-occ);
//    result=vec3(1-occ)*(0.5+0.5*sd.normal);//run this
    
    
//    float gamma=0.3;
//    result.x=pow(result.x,gamma);
//    result.y=pow(result.y,gamma);
//    result.z=pow(result.z,gamma);
    
}

void final_color(int x,int y,int w,int h, vec3&result){
    vec2 uv=vec2(x,y)/vec2(w,h);
    uv-=0.5;
    uv.x*=w/h;
    final_color(pt::cam_ray(uv,camPos,lookAt,1), result);
}

vec3 col(int x,int y,int w,int h){
    vec3 v;
    final_color(x,y,w,h,v);
    return v;
}

int main(){
    zoe.load_from_file("ZoeBackgroundMin1.ppm");
    printf("Zoe loaded\n");
    
    ppm_image img;
    img.set_size(500, 500);
    printf("Size set\n");
    
    img.alloc_mem();
    printf("Mem alloc\n");
    
    
    sp=new pt::sphere(vec3(0),0.2);
    ground=new pt::plane(Y_AXIS3,ORIGIN3);
    
    list=new pt::list();
    list->clear();
    list->add(ground);
    list->add(new pt::plane(X_AXIS3,ORIGIN3));
    list->add(new pt::plane(-1.0*Y_AXIS3,vec3(0,3,0)));
    list->add(new pt::plane(Z_AXIS3,ORIGIN3));
    list->add(new pt::aabb(vec3(0),vec3(2)));
    for(int x=0;x<5;x++){
        for(int y=-1;y<2;y++){
            for(int z=0;z<5;z++){
//                list->add(new pt::sphere(vec3(x*1.0,y,z*1.0),0.3));
                list->add(new pt::aabb( vec3(x,y,z),vec3(x,y,z)+0.2  ));
            }
        }
    }
    list->add(new pt::aabb(vec3(0),vec3(3,0.2,3)));
    printf("Initialized\n");

    int w=img.get_w();
    int h=img.get_h();
    
    for(int x=0;x<img.get_w();x++){
        for(int y=0;y<img.get_h();y++){
            vec3 result;
            final_color(x,y, img.get_w(),img.get_h(), result);
            img.set_pixel(x,y, result );
//            vec3 v;
//            v+=col(x+0.25,y+0.25,w,h);
//            v+=col(x+0.25,y+0.75,w,h);
//            v+=col(x+0.75,y+0.25,w,h);
//            v+=col(x+0.75,y+0.75,w,h);
//            v/=4;
//            int n=10;
//            for(int i=0;i<n;i++){
//                v+=col(x+rand_1()*4.0-2.0,y+rand_1()+4.0-2.0,w,h);
//            }
//            img.set_pixel(x,y,v/n);
//            img.set_pixel(x,y, zoe.get_pixel(vec2(1.0*x/w,1.0*y/h)));
        }
//        if(x%(w/500)==0){
//            float percentage=100.0*x/w;
//            printf("Percentage computed: %f%%\n",percentage);
//        }
        printf("%i/%i\n",x,w);
    }
    printf("Computed\n");
    
    img.clamp();
    printf("Clamped\n");
    
    ppm_image post;
    post.set_size(w,h);
    post.alloc_mem();
    int n=0;
    for(int x=0;x<w;x++){
        for(int y=0;y<h;y++){
            vec3 v=vec3(0);
            //Antialiasing: averaging pixels, for n=0 this is "passthrough"
            for(int i=-n;i<=n;i++){
                for(int j=-n;j<=n;j++){
                    v+=img.get_pixel(x+i,y+j);
                }
            }
            post.set_pixel(x,y, v/(2*n+1)/(2*n+1)  );
        }
        if(x%(w/100)==0){
            float percentage=100.0*x/w;
            printf("Percentage postprocessed: %i%%\n",(int)percentage);
        }
    }
    printf("Postprocessed\n");
    
    post.save("result-1.ppm");
    printf("Saved\n");
    
    img.dealloc();
    zoe.dealloc();
    printf("Dealloced\n");
    
    return 0;
}
