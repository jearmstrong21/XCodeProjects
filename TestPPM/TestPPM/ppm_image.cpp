

#include "ppm_image.h"

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

void ppm_image::set_pixel(int x, int y, float r, float g, float b){
    int i=get_ind(x, y);
    r_comp[i]=r;
    g_comp[i]=g;
    b_comp[i]=b;
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
