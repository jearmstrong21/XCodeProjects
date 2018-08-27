
#include "ppm_image.hpp"

#include "pt.hpp"

#include "pt_obj.hpp"
#include "pt_sphere.hpp"
#include "pt_list.hpp"
#include "pt_plane.hpp"

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

void final_color(int x,int y,int w,int h,vec3& result){
    result=vec3(0);
    
    vec2 uv=vec2(x,y)/vec2(w,h);
    uv-=0.5;
    uv.x*=w/h;
    
    pt::ray cam_ray=pt::cam_ray(uv, camPos, lookAt, 1);
    
    float t;
    vec3 n;
    pt::obj *o=NULL;
    bool intersection_found = list->intersect(cam_ray, t, n, o);
//    bool intersection_found=sp->intersect(cam_ray,t,n,o);
//    bool intersection_found=ground->intersect(cam_ray,t,n,o);
    if(!intersection_found)return;
    
    vec3 ray_end=cam_ray.pos+cam_ray.dir*t;
    
    result=vec3(0.5+0.5*n);
    
    vec3 n0=n;
    vec3 light_pos=vec3(6,2,7);
    vec3 d=vec3::normalize(light_pos-ray_end);
    bool in_shadow=list->intersect(pt::ray(ray_end+d*1e-3,d),  t,n,o);
    if(in_shadow&&t<vec3::length(ray_end-light_pos))result*=0;
    else result*=math::clamp(vec3::dot(n0,vec3::normalize(light_pos-ray_end)),0,1);
    float gamma=0.3;
    result.x=pow(result.x,gamma);
    result.y=pow(result.y,gamma);
    result.z=pow(result.z,gamma);

    
//
//    float t;
//    if(sp.intersect(cam_ray,t)){
//        vec3 intersect=cam_ray.pos+t*cam_ray.dir;
//        vec3 normal=vec3::normalize(intersect);
//        float x=normal.x;
//        float y=normal.y;
//        float z=normal.z;
////        float u=math::lin_remap(acos(z),-1,1,0,1);
////        float v=math::lin_remap(atan2(y,x),-PI,PI,0,1);
//        float r=vec3::length(normal);
//        float u=math::lin_remap(acos(z/r),0,PI,0,1);
//        float v=math::lin_remap(atan2(y,x),-PI,PI,0,1);
////        printf("%f,%f\n",u,v);
////        assert(u>0&&u<1&&v>0&&v<1);
////        float u=math::lin_remap(x,-1,1,0,1);
////        float v=math::lin_remap(y,-1,1,0,1);
//
//        int u_i=round(u*10);
//        int v_i=round(v*10);
//
//        u_i%=2;
//        v_i%=2;
////        u=math::clamp(u,0,1);
////        v=math::clamp(v,0,1);
////        result=vec3(0.5+0.5*normal);
//        result=vec3((u_i+v_i)%2)*0.3+0.3;
////        printf("%f, %f\n",u,v);
////        result=zoe.get_pixel( math::lin_remap(u,0,1,0,zoe.get_w())  ,  math::lin_remap(v,0,1,0,zoe.get_h()) );
//    }
    
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
    img.set_size(1000, 1000);
    printf("Size set\n");
    
    img.alloc_mem();
    printf("Mem alloc\n");
    
    
    sp=new pt::sphere(vec3(0),0.2);
    ground=new pt::plane(Y_AXIS3,ORIGIN3);
    
    list=new pt::list();
    list->clear();
    list->add(ground);
    list->add(new pt::plane(X_AXIS3,ORIGIN3));
    list->add(new pt::plane(Z_AXIS3,ORIGIN3));
    list->add(new pt::plane(-1.0*Y_AXIS3,vec3(0,3,0)));
    for(int x=0;x<5;x++){
        for(int y=-1;y<2;y++){
            for(int z=0;z<5;z++){
                list->add(new pt::sphere(vec3(x*1.0,y,z*1.0),0.2));
            }
        }
    }
    printf("Initialized\n");

    int w=img.get_w();
    int h=img.get_h();
    
    for(int x=0;x<img.get_w();x++){
        for(int y=0;y<img.get_h();y++){
            vec3 result;
            final_color(x,y, img.get_w(),img.get_h(), result);
            img.set_pixel(x,y, result );
//            img.set_pixel(x,y, zoe.get_pixel(vec2(1.0*x/w,1.0*y/h)));
        }
        if(x%(w/100)==0){
            float percentage=100.0*x/w;
            printf("Percentage computed: %i%%\n",(int)percentage);
        }
    }
    printf("Computed\n");
    
    img.clamp();
    printf("Clamped\n");
    
    ppm_image post;
    post.set_size(w,h);
    post.alloc_mem();
    int n=1;
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
