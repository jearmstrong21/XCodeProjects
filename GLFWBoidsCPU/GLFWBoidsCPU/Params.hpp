//
//  Params.hpp
//  GLFWBoidsCPU
//
//  Created by Jack Armstrong on 5/28/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef Params_hpp
#define Params_hpp

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
    
    
    Params();
};

#endif /* Params_hpp */
