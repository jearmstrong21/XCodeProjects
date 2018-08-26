

#ifndef ppm_image_hpp
#define ppm_image_hpp

#include <fstream>
#include <string>
#include "math/vec3.hpp"
#include "math/math.hpp"

#define ppm_image_PRECISION 1000

using math::vec3;

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
    
    void clamp();
    
    void set_pixel(int x,int y, float r,float g,float b);//0 to 1 rnage
    void set_pixel(int x,int y, vec3 p);
    void save(std::string fn);
};

#endif
