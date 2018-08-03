
#include <stdlib.h>

#include <iostream>
#include <fstream>

#include "ppm_image.h"

int main(){
    
    ppm_image img;
    img.set_size(10, 25);
    img.alloc_mem();
    
    for(int x=0;x<img.get_w();x++){
        for(int y=0;y<img.get_h();y++){
            img.set_pixel(x, y, 1.0f*x/img.get_w(), 1.0f*y/img.get_h(), 0);
        }
    }
    
    img.save("test.ppm");
    
    return 0;
}
