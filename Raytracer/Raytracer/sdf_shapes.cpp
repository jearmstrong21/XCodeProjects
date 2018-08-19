
//
//  sdf_shapes.cpp
//  Raytracer
//
//  Created by Jack Armstrong on 8/18/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "sdf_shapes.hpp"

namespace sdf{
    
    float sdSphere(vec3 p,float s){
        return vec3::length(p)-s;
    }
    
    float udBox(vec3 p,vec3 b){
        return vec3::length(vec3::max(vec3::abs(p)-b,0));
    }
    
    float udRoundBox(vec3 p,vec3 b,float r){
        return vec3::length(vec3::max(vec3::abs(p)-b,0))-r;
    }
    
    float sdBox(vec3 p,vec3 b){
        vec3 d=vec3::abs(p)-b;
        return math::min(math::max(d.x,math::max(d.y,d.z)),0)+vec3::length(vec3::max(d,0));
    }
    
    float sdTorus(vec3 p,vec2 t){
        vec2 q=vec2(vec2::length(vec2(p.x,p.z))-t.x,p.y);
        return vec2::length(q)-t.y;
    }
    
    float sdCylinder(vec3 p,vec3 c){
        return vec2::length(vec2(p.x,p.z)-vec2(c.x,c.y))-c.z;
    }
    
    float sdCone(vec3 p,vec2 c){
        float q=vec2::length(vec2(p.x,p.y));
        return vec2::dot(vec2::normalize(c),vec2(q,p.z));
    }
    
    float sdPlane(vec3 p,vec4 n){
        return vec3::dot(p,vec3(n.x,n.y,n.z))+n.w;
    }
    
    float sdHexPrism(vec3 p,vec2 h){
        vec3 q=vec3::abs(p);
        return math::max(q.z-h.y,math::max((q.x*0.866025+q.y*0.5),q.y)-h.x);
    }
    
    float sdTriPrism(vec3 p,vec2 h){
        vec3 q=vec3::abs(p);
        return math::max(q.z-h.y,math::max(q.x*0.866025+p.y*0.5,-p.y)-h.x*0.5);
    }
    
    float sdCapsule(vec3 p,vec3 a,vec3 b,float r){
        vec3 pa=p-a;
        vec3 ba=b-a;
        float h=math::clamp(vec3::dot(pa,ba)/vec3::dot(ba,ba),0,1);
        return vec3::length(pa-ba*h)-r;
    }
    
    float sdCappedCylinder(vec3 p,vec2 h){
        vec2 d = vec2::abs(vec2(vec2::length(vec2(p.x,p.z)),p.y)) - h;
        return math::min(math::max(d.x,d.y),0.0) + vec2::length(vec2::max(d,0.0));
    }
    
    float sdCappedCone(vec3 p,vec3 c){
        vec2 q = vec2( vec2::length(vec2(p.x,p.z)), p.y );
        vec2 v = vec2( c.z*c.y/c.x, -c.z );
        vec2 w = v - q;
        vec2 vv = vec2( vec2::dot(v,v), v.x*v.x );
        vec2 qv = vec2( vec2::dot(v,w), v.x*w.x );
        vec2 d = vec2::max(qv,0.0)*qv/vv;
        return sqrt( vec2::dot(w,w) - math::max(d.x,d.y) ) * math::sign(math::max(q.y*v.x-q.x*v.y,w.y));
    }
    
    float sdEllipsoid(vec3 p,vec3 r){
        return (vec3::length(p/r)-1)*math::min(math::min(r.x,r.y),r.z);
    }
    
    float udTriangle( vec3 p, vec3 a, vec3 b, vec3 c ) {
        vec3 ba = b - a; vec3 pa = p - a;
        vec3 cb = c - b; vec3 pb = p - b;
        vec3 ac = a - c; vec3 pc = p - c;
        vec3 nor = vec3::cross( ba, ac );
        
        return sqrt(
                    (math::sign(vec3::dot(vec3::cross(ba,nor),pa)) +
                     math::sign(vec3::dot(vec3::cross(cb,nor),pb)) +
                     math::sign(vec3::dot(vec3::cross(ac,nor),pc))<2.0)
                    ?
                    math::min( math::min(
                                         vec3::dot2(ba*math::clamp(vec3::dot(ba,pa)/vec3::dot2(ba),0.0,1.0)-pa),
                                         vec3::dot2(cb*math::clamp(vec3::dot(cb,pb)/vec3::dot2(cb),0.0,1.0)-pb) ),
                                         vec3::dot2(ac*math::clamp(vec3::dot(ac,pc)/vec3::dot2(ac),0.0,1.0)-pc) )
                    :
                    vec3::dot(nor,pa)*vec3::dot(nor,pa)/vec3::dot2(nor) );
    }
    
    float udQuad( vec3 p, vec3 a, vec3 b, vec3 c, vec3 d )
    {
        vec3 ba = b - a; vec3 pa = p - a;
        vec3 cb = c - b; vec3 pb = p - b;
        vec3 dc = d - c; vec3 pc = p - c;
        vec3 ad = a - d; vec3 pd = p - d;
        vec3 nor = vec3::cross( ba, ad );
        
        return sqrt(
                    (math::sign(vec3::dot(vec3::cross(ba,nor),pa)) +
                     math::sign(vec3::dot(vec3::cross(cb,nor),pb)) +
                     math::sign(vec3::dot(vec3::cross(dc,nor),pc)) +
                     math::sign(vec3::dot(vec3::cross(ad,nor),pd))<3.0)
                    ?
                    math::min( math::min( math::min(
                                  vec3::dot2(ba*math::clamp(vec3::dot(ba,pa)/vec3::dot2(ba),0.0,1.0)-pa),
                                  vec3::dot2(cb*math::clamp(vec3::dot(cb,pb)/vec3::dot2(cb),0.0,1.0)-pb) ),
                             vec3::dot2(dc*math::clamp(vec3::dot(dc,pc)/vec3::dot2(dc),0.0,1.0)-pc) ),
                        vec3::dot2(ad*math::clamp(vec3::dot(ad,pd)/vec3::dot2(ad),0.0,1.0)-pd) )
                    :
                    vec3::dot(nor,pa)*vec3::dot(nor,pa)/vec3::dot2(nor) );
    }
    
    float sdTorus82(vec3 p,vec2 t){
        vec2 q=vec2(vec2::dot2(vec2(p.x,p.z))-t.x,p.y);
        return vec2::length8(q)-t.y;
    }
    
    float sdTorus88( vec3 p, vec2 t ){
        vec2 q = vec2(vec2::length8(vec2(p.x,p.z))-t.x,p.y);
        return vec2::length8(q)-t.y;
    }
    
}
