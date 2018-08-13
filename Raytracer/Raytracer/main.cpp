//
//  main.cpp
//  Raytracer1
//
//  Created by Jack Armstrong on 8/3/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "ppm_image.hpp"

#include "complex.hpp"
#include "hsv.hpp"

using math::complex;

int main(int argc, const char * argv[]) {
    ppm_image img;
    img.set_size(500, 500);
    img.alloc_mem();
    
    
    printf("Starting loop\n");
    
    
    for(int x=0;x<img.get_w();x++){
        for(int y=0;y<img.get_h();y++){
            complex c0=complex::to_polar(math::lin_remap(x,0,img.get_w(),-2,2),math::lin_remap(y,0,img.get_h(),-2,2));
            complex c=c0;
            float i=0;
            float max=20;
            float d=1000000;
            for(;i<max;i++){
                if(c.r>40)break;
                c=c*c+c0;
                d=math::min(d,complex::length(c-complex::to_polar(0.4,0.2)));
            }
            
//            if(i<max){
//                float log_zn=log(c.r*c.r)/2;
//                float nu=log(log_zn/log(2))/log(2);
//                i=i+1-nu;
//            }
            
//            float f=i/max;
            float f=d;
//            float f=complex::length(c-complex::to_polar(0.4,0.2));
//            img.set_pixel(x,y,  f,f,f);
            float r=colors::h2r(f);
            float g=colors::h2g(f);
            float b=colors::h2b(f);
            float mult=math::clamp(0.6+pow(2.0,-c.r),0,1);
            r*=mult;
            g*=mult;
            b*=mult;
            img.set_pixel(x,y,  r,g,b);
//            if(i==max)img.set_pixel(x,y, 0,0,0);
        }
    }
    
    printf("Finished computation\n");
    
    img.save("result-1.ppm");
    
    printf("Saved to disk\n");
    
    return 0;
}
