//
//  Hue.hpp
//  GLFWBoidsCPU
//
//  Created by Jack Armstrong on 5/29/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef Hue_hpp
#define Hue_hpp

#include "Math.hpp"

namespace Hue{
    
    float constrainAngle(float);
    
    float hueToR(float h);
    float hueToG(float h);
    float hueToB(float h);
    
    float rgbToHue(float r,float g,float b);
};

#endif /* Hue_hpp */
