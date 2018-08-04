//
//  HSB.hpp
//  StableFluidSimulation
//
//  Created by Jack Armstrong on 8/4/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef HSB_hpp
#define HSB_hpp


float norm(float t,float a,float b) {
    return (t-a)/(b-a);
}

float lerp(float t,float a,float b) {
    return a+t*(b-a);
}


float clamp(float t,float a,float b) {
    if(t<a)return a;
    if(t>b)return b;
    return t;
}

bool isInRange(float t,float a,float b) {
    return t==clamp(t,a,b);
}

float map(float t,float s1,float e1,float s2,float e2) {
    return lerp(norm(t,s1,e1),s2,e2);
}


float thetaToR(float theta) {//in range 0 to 1
    theta=round(fmod(theta,1)*360);
    if(isInRange(theta, 0, 60))return 1;
    if(isInRange(theta, 60, 120))return map(theta, 60, 120, 1, 0);
    if(isInRange(theta, 120, 180))return 0;
    if(isInRange(theta, 180, 240))return 0;
    if(isInRange(theta, 240, 300))return map(theta, 240, 300, 0, 1);
    if(isInRange(theta, 300, 360))return 0;
    return 0;
}

float thetaToG(float theta) {//in range 0 to 1
    theta=round(fmod(theta,1)*360);
    if(isInRange(theta, 0, 60))return map(theta, 0, 60, 0, 1);
    if(isInRange(theta, 60, 120))return 1;
    if(isInRange(theta, 120, 180))return 1;
    if(isInRange(theta, 180, 240))return map(theta, 180, 240, 1, 0);
    if(isInRange(theta, 240, 300))return 0;
    if(isInRange(theta, 300, 360))return 0;
    return 0;
}

float thetaToB(float theta) {//in range 0 to 1
    theta=round(fmod(theta,1)*360);
    if(isInRange(theta, 0, 60))return 0;
    if(isInRange(theta, 60, 120))return 0;
    if(isInRange(theta, 120, 180))return map(theta, 120, 180, 0, 1);
    if(isInRange(theta, 180, 240))return 1;
    if(isInRange(theta, 240, 300))return 1;
    if(isInRange(theta, 300, 360))return map(theta, 300, 360, 1, 0);
    return 0;
}

#endif /* HSB_hpp */
