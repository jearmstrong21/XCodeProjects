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

using math::complex;
using math::vec2;

int main(int argc, const char * argv[]) {
    ppm_image img;
    img.set_size(500, 500);
    img.alloc_mem();
    
    
    printf("Starting loop\n");
    
    
    for(int x=0;x<img.get_w();x++){
        for(int y=0;y<img.get_h();y++){
        }
    }
    
    printf("Finished computation\n");
    
    img.save("result-1.ppm");
    
    printf("Saved to disk\n");
    
    return 0;
}
