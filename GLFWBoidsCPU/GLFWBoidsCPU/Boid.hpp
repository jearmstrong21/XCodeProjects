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
#include <glm/gtx/norm.hpp>
#include "Params.hpp"
#include <cmath>
#include <vector>
#include "Math.hpp"
#include "Hue.hpp"

using glm::vec2;
using glm::vec3;
using glm::angle;
using glm::normalize;
using glm::length2;
using std::atan2f;
using std::vector;

#define PI 3.14159265359

class Boid {
public:
    VO vo;
    vec2 pos;
    vec2 vel;
    vec2 acc;
    int id;
    
    Boid(int theID);
    
    void init(Params* params);
    
    void wrapPos();
    
    void draw(Params*params,ShaderProgram*shader);
    
    void freeMem();
    
    void update(vector<Boid>* boids,Params*params);
};

#endif /* Boid_hpp */
