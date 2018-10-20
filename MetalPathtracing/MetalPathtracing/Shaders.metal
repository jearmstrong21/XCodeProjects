//
//  Shaders.metal
//  MetalPathtracing
//
//  Created by Jack Armstrong on 10/16/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <metal_stdlib>
using namespace metal;

struct VertexOut {
    float4 position [[position]];
    float2 uv;
};

vertex VertexOut vertexShader(const device packed_float3* position [[buffer(0)]], const device packed_float2* uv [[buffer(1)]], unsigned int vid [[vertex_id]]) {
    VertexOut vout;
    vout.position = float4(position[vid],1);
    vout.uv=uv[vid];
    return vout;
}

struct Ray {
    float3 pos;
    float3 dir;
};

struct Sphere {
    float3 pos;
    float rad;
    Sphere(float3 p,float r){pos=p;rad=r;}
};

struct Plane {
    float3 pos;
    float3 normal;
    Plane(float3 p,float3 n){pos=p;normal=normalize(n);}
};

struct RayHit {
    float t;
    float3 normal;
    bool hit;
    RayHit(bool b){hit=b;}
    RayHit(float _t,float3 n){hit=true;t=_t;normal=n;}
};


constant RayHit NO_HIT=RayHit(false);

RayHit iSphere(Sphere sphere,Ray ray){
    float a=dot(ray.dir,ray.dir);
    float b=2*dot(ray.pos-sphere.pos,ray.dir);
    float c=dot(ray.pos-sphere.pos,ray.pos-sphere.pos)-sphere.rad*sphere.rad;
    float discr=b*b-4*a*c;
    if(discr<0)return NO_HIT;
    float sqrtDiscr=sqrt(discr);
    float t=min((-b+sqrtDiscr)/(2*a),(-b-sqrtDiscr)/(2*a));
    return RayHit(t,normalize(ray.pos+t*ray.dir-sphere.pos));
}

RayHit iPlane(Plane plane,Ray ray){
    float t=dot(plane.pos-ray.pos,plane.normal)/dot(ray.dir,plane.normal);
    if(t<0)return NO_HIT;
    return RayHit(t,plane.normal);
}

RayHit minHit(RayHit a,RayHit b){
    if(!a.hit)return b;
    if(!b.hit)return a;
    if(a.t<b.t)return a;
    return b;
}

RayHit minHit(RayHit a,RayHit b,RayHit c){
    return minHit(a,minHit(b,c));
}

RayHit minHit(RayHit a,RayHit b,RayHit c,RayHit d){
    return minHit(a,minHit(b,c,d));
}

float3 phong(float3 ambient,float3 diffuse,float3 specular,float shininess,float3 camPos,float3 pos,float3 normal,float3 light){
    float diffuseMult=clamp(dot(normal,normalize(light-pos)),0.0f,1.0f);
    float specularMult=clamp( pow(  dot(normalize(light-pos),reflect(normalize(pos-camPos),normal))  , shininess)  ,0.0f, 1.0f);
    return ambient+diffuseMult*diffuse+specularMult*specular;
}

fragment float4 fragmentShader(VertexOut vout [[stage_in]], const device float& width [[buffer(0)]], const device float& height [[buffer(1)]], const device float& time [[buffer(2)]]){
    float2 uv = vout.uv;
    uv*=2;
    uv-=1;
    uv.x*=width/height;
    
    float3 camPos = float3(4*cos(time*.3),2,3*sin(time*.6));
    float3 lookAt = float3(0,0,0);
    float zoom = 1;
    
    float3 lightPos = float3(8,3,5);

    Ray ray;
    ray.pos=camPos;
    
    float3 f=normalize(lookAt-camPos);
    float3 r=cross(float3(0,1,0),f);
    float3 u=cross(f,r);
    
    float3 c=camPos+f*zoom;
    float3 i=c+uv.x*r+uv.y*u;
    ray.dir=normalize(i-camPos);
    
    Sphere sphere=Sphere(float3(0,0,0),1);
    Plane plane1=Plane(float3(0,0,0),float3(0,1,0));
    Plane plane2=Plane(float3(-5,0,0),float3(1,0,0));
    Plane plane3=Plane(float3(0,0,-5),float3(0,0,1));
    RayHit hit=minHit(iSphere(sphere,ray),iPlane(plane1,ray),iPlane(plane2,ray),iPlane(plane3,ray));
    
    float3 ambient=float3(0);
    float3 diffuse=float3(0.75);
    float3 specular=float3(0.25);
    float shininess=100;
    
    float3 phongRes=phong(ambient,diffuse,specular,shininess,camPos,ray.pos+hit.t*ray.dir,hit.normal,lightPos);
//    return float4(uv,0,1);
    if(hit.hit)return float4(phongRes,1);
    else return float4(ambient,1);
//    return float4(.5*hit.normal+.5,1);
}
