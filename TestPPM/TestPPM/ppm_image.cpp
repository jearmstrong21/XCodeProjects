

#include "ppm_image.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ppm_image::ppm_image(){
    
}

int ppm_image::get_ind(int x, int y){
    return x+y*width;
}

void ppm_image::set_size(int w, int h){
    width=w;
    height=h;
}

int ppm_image::get_w(){
    return width;
}

int ppm_image::get_h(){
    return height;
}

void ppm_image::alloc_mem(){
    r_comp=(float*)malloc(sizeof(float)*width*height);
    g_comp=(float*)malloc(sizeof(float)*width*height);
    b_comp=(float*)malloc(sizeof(float)*width*height);
    
    for(int i=0;i<width*height;i++){
        r_comp[i]=g_comp[i]=b_comp[i]=0;
    }
}

void ppm_image::load_from_file(std::string fn){
    std::ifstream file(fn);
    std::string header;
    file>>header;
    int _1,_2;
    file>>_1;//w
    file>>_2;//h
    float prec;
    file>>prec;
    
    int w;
    int h;
    int channels;
    unsigned char* data=stbi_load(fn.c_str(),&w,&h,&channels,3);
//    printf("Channels: %i\n",channels);
//    printf("W: %i\nH: %i\n",w,h);
    set_size(w,h);
    alloc_mem();
    int i=0;
    for(int x=0;x<w;x++){
        for(int y=0;y<h;y++){
            unsigned bytePerPixel = channels;
            unsigned char* pixelOffset = data + (x + w * y) * bytePerPixel;
            unsigned char r = pixelOffset[0];
            unsigned char g = pixelOffset[1];
            unsigned char b = pixelOffset[2];
            set_pixel(x,y, vec3(r,g,b)/prec  );
            i++;
        }
    }

    clamp();
}

vec3 ppm_image::get_pixel(vec2 uv){
    return get_pixel(uv.x*width,uv.y*height);
}

void ppm_image::set_pixel(int x, int y, float r, float g, float b){
    int i=get_ind(x, y);
    r_comp[i]=r;
    g_comp[i]=g;
    b_comp[i]=b;
}

void ppm_image::set_pixel(int x,int y, vec3 p){
    set_pixel(x,y, p.x,p.y,p.z );
}

void ppm_image::clamp(){
    for(int x=0;x<width;x++){
        for(int y=0;y<height;y++){
            int i=get_ind(x, y);
            r_comp[i]=math::clamp(r_comp[i],0,1);
            g_comp[i]=math::clamp(g_comp[i],0,1);
            b_comp[i]=math::clamp(b_comp[i],0,1);
        }
    }
    
}

vec3 ppm_image::get_pixel(int x,int y){
    int i=get_ind(math::clamp(x,0,width-1),math::clamp(y,0,height-1));
    return vec3(r_comp[i],g_comp[i],b_comp[i]);
}

void ppm_image::dealloc(){
    delete [] r_comp;
    delete [] g_comp;
    delete [] b_comp;
}

void ppm_image::save(std::string fn){
    std::ofstream file;
    file.open(fn.c_str());
    
    file<<"P3\n";
    file<<width<<" "<<height<<"\n";
    file<<ppm_image_PRECISION<<"\n";
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
            int i=get_ind(x, y);
            file<<(int)(r_comp[i]*ppm_image_PRECISION)<<" "<<(int)(g_comp[i]*ppm_image_PRECISION)<<" "<<(int)(b_comp[i]*ppm_image_PRECISION)<<" ";
        }
        file<<"\n";
    }
    
    file.close();
}
