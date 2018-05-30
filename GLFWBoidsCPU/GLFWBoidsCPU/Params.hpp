//
//  Params.hpp
//  GLFWBoidsCPU
//
//  Created by Jack Armstrong on 5/28/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef Params_hpp
#define Params_hpp

#include <glm/glm.hpp>

using glm::vec2;

class Params{
public:
    //render boid
    float boidSize;
    
    //update boid
    float boidAttractDist;
    float boidAttractPosMult;
    float boidAttractVelMult;
    float boidSepDist;
    float boidSepMult;
    float boidMaxVel;
    float boidStayInBorders;
    vec2 boidMinPos;
    vec2 boidMaxPos;
    vec2 boidWorldCenter;
    
    Params();
};

#endif /* Params_hpp */
