//
//  sdf_shapes.hpp
//  Raytracer
//
//  Created by Jack Armstrong on 8/18/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef sdf_shapes_hpp
#define sdf_shapes_hpp

#include <stdio.h>
#include <cmath>
#include "vec4.hpp"
#include "vec3.hpp"
#include "vec2.hpp"

using math::vec4;
using math::vec3;
using math::vec2;

namespace sdf {
    //https://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
    float sdSphere(vec3 p,float s);
    float udBox(vec3 p,vec3 b);
    float sdBox(vec3 p,vec3 b);
    float sdTorus(vec3 p,vec2 t);
    float sdCylinder(vec3 p,vec3 c);
    float sdCone(vec3 p,vec2 c);
    float sdPlane(vec3 p,vec4 n);
    float sdHexPrism(vec3 p,vec2 h);
    float sdTriPrism(vec3 p,vec2 h);
    float sdCapsule(vec3 p,vec3 a,vec3 b,float r);
    float sdCappedCone(vec3 p,vec3 c);
    float sdEllipsoid(vec3 p,vec3 r);
    float udTriangle(vec3 p,vec3 a,vec3 b,vec3 c);
    float udQuad(vec3 p,vec3 a,vec3 b,vec3 c,vec3 d);
    float sdTorus82(vec3 p,vec2 t);
    float sdTorus88(vec3 p,vec2 t);
    
}

#endif /* sdf_shapes_hpp */
