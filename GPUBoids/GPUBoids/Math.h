//
//  Math.h
//  HelloOpenCL
//
//  Created by Jack Armstrong on 6/24/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef Math_h
#define Math_h

namespace Math{

float lerp(float start,float end,float t){
    return (1 - t) * start + t * end;
}

float norm(float start,float end,float t){
    return (t-start)/(end-start);
}

float map(float t,float start1,float end1,float start2,float end2){
    return Math::lerp(start2,end2,Math::norm(start1,end1,t));
}
};

#endif /* Math_h */
