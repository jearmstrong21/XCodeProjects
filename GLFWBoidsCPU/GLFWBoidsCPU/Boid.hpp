//
//  Boid.hpp
//  GLFWBoidsCPU
//
//  Created by Jack Armstrong on 5/28/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef Boid_hpp
#define Boid_hpp

#include "VO.hpp"
#include "ShaderProgram.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Params.hpp"
#include <cmath>

using glm::vec2;
using glm::vec3;
using glm::angle;
using std::atan2f;

#define PI 3.14159265359

class Boid {
public:
    VO vo;
    ShaderProgram shader;
    vec2 pos;
    vec2 vel;
    vec2 acc;
    
    Boid();
    
    void init(Params* params);
    
    void wrap();
    
    void draw();
    
    void update();
};

#endif /* Boid_hpp */
