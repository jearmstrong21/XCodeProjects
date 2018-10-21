//
//  Shaders.metal
//  MetalPathtracing
//
//  Created by Jack Armstrong on 10/16/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <metal_stdlib>
using namespace metal;

#include "loki_header.metal"

#define PI 3.14159265359

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

struct AABB {
    float3 mi;
    float3 ma;
    AABB(float3 i,float3 a){mi=i;ma=a;}
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

#define swap(a,b)  {float DEFINED_TEMP=a;a=b;b=DEFINED_TEMP;}

RayHit iAABB(AABB aabb,Ray ray){
    float3 mi=aabb.mi;
    float3 ma=aabb.ma;
    float tmin=(mi.x-ray.pos.x)/ray.dir.x;
    float tmax=(ma.x-ray.pos.x)/ray.dir.x;
    
    if(tmin>tmax)swap(tmin,tmax);
    
    float tymin=(mi.y-ray.pos.y)/ray.dir.y;
    float tymax=(ma.y-ray.pos.y)/ray.dir.y;
    
    if(tymin>tymax)swap(tymin,tymax);
    
    if(tmin>tymax||tymin>tmax){
        return NO_HIT;
    }
    
    if(tymin>tmin){
        tmin=tymin;
    }
    
    if(tymax<tmax){
        tmax=tymax;
    }
    
    float tzmin=(mi.z-ray.pos.z)/ray.dir.z;
    float tzmax=(ma.z-ray.pos.z)/ray.dir.z;
    
    if(tzmin>tzmax)swap(tzmin,tzmax);
    
    if(tmin>tzmax||tzmin>tmax){
        return NO_HIT;
    }
    
    if(tzmin>tmin){
        tmin=tzmin;
    }
    
    if(tzmax<tmax){
        tmax=tzmax;
    }
    
    float t=tmin;
    
    if(t<0){
        t=tmax;
        if(t<0)return NO_HIT;
    }
    
    RayHit hit=NO_HIT;
    hit.hit=true;
    hit.t=t;
    
    float3 end=ray.pos+(hit.t-0.0001f)*ray.dir;
    if(end.x<mi.x)hit.normal=float3(-1,0,0);
    if(end.x>ma.x)hit.normal=float3( 1,0,0);
    if(end.y<mi.y)hit.normal=float3(0,-1,0);
    if(end.y>ma.y)hit.normal=float3(0, 1,0);
    if(end.z<mi.z)hit.normal=float3(0,0,-1);
    if(end.z>ma.z)hit.normal=float3(0,0, 1);
    return hit;
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
RayHit minHit(RayHit a,RayHit b,RayHit c,RayHit d,RayHit e){
    return minHit(a,minHit(b,c,d,e));
}
RayHit minHit(RayHit a,RayHit b,RayHit c,RayHit d,RayHit e,RayHit f){
    return minHit(a,minHit(b,c,d,e,f));
}

float3 phong(float3 diffuse,float3 specular,float shininess,float3 camPos,float3 pos,float3 normal,float3 light){
    float diffuseMult=clamp(dot(normal,normalize(light-pos)),0.0f,1.0f);
    float specularMult=clamp( pow(  dot(normalize(light-pos),reflect(normalize(pos-camPos),normal))  , shininess)  ,0.0f, 1.0f);
    return diffuseMult*diffuse+specularMult*specular;
}

float3 clampColor(float3 c){
    if(all(c==clamp(c,float3(0),float3(1))))return c;
    c/=max(c.x,max(c.y,c.z));
//    c/=length(c);
    return c;
}

fragment float4 fragmentShader(VertexOut vout [[stage_in]], const device float& width [[buffer(0)]], const device float& height [[buffer(1)]], const device float& time [[buffer(2)]],const device int& frames [[buffer(3)]]){
    int seedX=(int)(vout.uv.x*width);
    int seedY=(int)(vout.uv.y*height);
    Loki rng=Loki(seedX,seedY,frames);
    float2 uv = vout.uv;
    uv*=2;
    uv-=1;
    uv.x*=width/height;
    
    float3 camPos = float3(4*cos(time*.3),1,3*sin(time*.3));
    float3 lookAt = float3(0,0,0);
    float zoom = 1;
    
#define SCENE 4
    
#if SCENE == 1
    //Scene 1
    Sphere sphere1=Sphere(float3(0,2+1.5*sin(time),0),0.5);lookAt=sphere1.pos;
    Plane plane1=Plane(float3(0,0,0),float3(0,1,0));
    Plane plane2=Plane(float3(-5,0,0),float3(1,0,0));
    Plane plane3=Plane(float3(0,0,-5),float3(0,0,1));
    AABB aabb1=AABB(float3(-.1,0,-.1),float3(0.1,3.5,0.1));
    AABB aabb2=AABB(float3(-1.4,0,-.7),float3(-.6,1,0.3));

#define intersectScene(r) (minHit(iSphere(sphere1,r),iPlane(plane1,r),iPlane(plane2,r),iPlane(plane3,r),iAABB(aabb1,r),iAABB(aabb2,r)))
#endif
    
#if SCENE == 2
    //Scene 2
    Sphere sphere1=Sphere(float3(0,2,0),1);
    Plane plane1=Plane(float3(0,0,0),float3(0,1,0));

#define intersectScene(r) (minHit(iSphere(sphere1,r),iPlane(plane1,r)))
#endif

#if SCENE == 3
    //Scene 3
    AABB aabb1=AABB(float3(-.3,0,-.3),float3(.3,1,.3));
    Plane plane1=Plane(float3(0,0,0),float3(0,1,0));

#define intersectScene(r) (minHit(iAABB(aabb1,r),iPlane(plane1,r)))
#endif
    
#if SCENE == 4
    //Scene 4
    Sphere sphere1=Sphere(float3(0,2+1.5*sin(time),0),0.5);lookAt=sphere1.pos;
    Plane plane1=Plane(float3(0,0,0),float3(0,1,0));
    AABB aabb1=AABB(float3(-.1,0,-.1),float3(0.1,3.5,0.1));
    AABB aabb2=AABB(float3(-1.4,0,-.7),float3(-.6,1,0.3));
    
#define intersectScene(r) (minHit(iSphere(sphere1,r),iPlane(plane1,r),iAABB(aabb1,r),iAABB(aabb2,r)))
#endif
    
    float3 lightPos = float3(8,5,2);
//    camPos=lightPos;

    Ray ray;
    ray.pos=camPos;
    
    float3 f=normalize(lookAt-camPos);
    float3 r=cross(float3(0,1,0),f);
    float3 u=cross(f,r);
    
    float3 c=camPos+f*zoom;
    float3 i=c+uv.x*r+uv.y*u;
    ray.dir=normalize(i-camPos);
    
    RayHit hit=intersectScene(ray);
    float3 rayEnd=ray.pos+hit.t*ray.dir;
    
    float3 ambient=float3(0,0,1);
    float3 diffuse=0.5*float3(1,0,0);
    float3 specular=0.3*float3(1,1,0);
    float shininess=400;
    
    float3 phongRes=phong(diffuse,specular,shininess,camPos,rayEnd,hit.normal,lightPos);
    
    
    float3 normal=hit.normal;
    //Ambient occlusion
#define NUM_AO_SAMPLES 100.0f
    float ao=0;
    {
        float3 w=normal;
        float3 v=cross(w,float3(0.0072,1,0.0034));
        v=normalize(v);
        float3 u=cross(v,w);
        for(int i=0;i<NUM_AO_SAMPLES;i++){
            float theta=rng.rand()*2*PI;
            float phi=rng.rand()*PI;
            float3 sampled=float3(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));
            float3 dir=normalize(sampled.x*u+sampled.y*v+sampled.z*w);// xyz to uvw
    //        float3 dir=sampled;
            Ray aoRay;
            aoRay.pos=rayEnd+dir*0.0001;
            aoRay.dir=dir;
            RayHit aoHit=intersectScene(aoRay);
            if(!aoHit.hit){
                ao++;
            }
        }
    }
    ao/=NUM_AO_SAMPLES;
    phongRes+=ambient*ao;
    phongRes=float3(ao);
    
    //Shadows
//    Ray shadowRay;
//    shadowRay.pos=lightPos;
//    shadowRay.dir=normalize(rayEnd-lightPos);
//    shadowRay.pos+=0.0001*shadowRay.dir;
//    RayHit shadowHit=intersectScene(shadowRay);
//    float3 shadowEnd=shadowRay.pos+shadowHit.t*shadowRay.dir;
//    if(abs(shadowHit.t-length(rayEnd-lightPos))>0.001)phongRes=ambient;
//    if(true)return 0.05f*float4(shadowHit.t);
    if(hit.hit)return float4(clampColor(phongRes),1);
    else return float4(ambient,1);
}
