
#include "ppm_image.hpp"

int main(){
    ppm_image img;
    img.set_size(500, 500);
    img.alloc_mem();
    
    for(int x=0;x<500;x++){
        for(int y=0;y<500;y++){
            img.set_pixel(x,y, x/500.0,y/500.0, 0 );
        }
    }
    
    img.clamp();
    img.save("result-1.ppm");
    img.dealloc();
    
    return 0;
}
