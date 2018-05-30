//
//  Hue.cpp
//  GLFWBoidsCPU
//
//  Created by Jack Armstrong on 5/29/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "Hue.hpp"


float Hue::constrainAngle(float ang){
    while(ang<0)ang+=360;
    while(ang>=360)ang-=360;
    return ang;
}

float Hue::hueToR(float h){
    
    if(h<60){
        return 1;
    }
    if(h<120){
        return Math::map(h,60,120,1,0);
    }
    if(h<240){
        return 0;
    }
    if(h<300){
        return Math::map(h,240,300,0,1);
    }
    if(h<360){
        return 1;
    }
    
    return 0;
}

float Hue::hueToG(float h){
    if(h<60){
        return Math::map(h,0,60,0,1);
    }
    if(h<180){
        return 1;
    }
    if(h<240){
        return Math::map(h,180,240,1,0);
    }
    if(h<360){
        return 0;
    }
    return 0;
}

float Hue::hueToB(float h){
    if(h<120){
        return 0;
    }
    if(h<180){
        return Math::map(h,120,180,0,1);
    }
    if(h<300){
        return 1;
    }
    if(h<360){
        return Math::map(h,300,360,1,0);
    }
    return 0;
}

float Hue::rgbToHue(float r,float g,float b){
    if(r==0){
        if(g==1){
            return Math::map(b,0,1,120,180);
        }else{
            return Math::map(g,1,0,180,240);
        }
    } else if(r==1){
        if(g==0){
            return Math::map(b,1,0,300,360);
        }else{
            return Math::map(g,0,1,0,60);
        }
    } else {
        if(g==1){
            return Math::map(r,1,0,60,120);
        }else{
            return Math::map(r,0,1,240,300);
        }
    }
    return 0;
}
