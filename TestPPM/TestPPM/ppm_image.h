//
//  ppm_image.h
//  TestPNGWriter
//
//  Created by Jack Armstrong on 8/3/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef ppm_image_h
#define ppm_image_h

#include <fstream>
#include <string>

#define ppm_image_PRECISION 1000

class ppm_image {
private:
    
    int width;
    int height;
    
    float* r_comp;
    float* g_comp;
    float* b_comp;
    
    int get_ind(int x,int y);
    
public:
    
    int get_w();
    int get_h();
    
    ppm_image();
    
    void set_size(int w, int h);
    
    void alloc_mem();
    
    void set_pixel(int x,int y, float r,float g,float b);//0 to 1 rnage
    
    void save(std::string fn);
};

#endif /* ppm_image_h */