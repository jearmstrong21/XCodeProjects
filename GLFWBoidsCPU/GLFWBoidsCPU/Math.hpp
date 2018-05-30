//
//  Math.hpp
//  GLFWBoidsCPU
//
//  Created by Jack Armstrong on 5/29/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef Math_hpp
#define Math_hpp

namespace Math{
    float lerp(float t,float a,float b);
    float norm(float t,float a,float b);
    float map(float t,float a,float b,float c,float d);
};

#endif /* Math_hpp */
