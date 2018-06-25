//
//  FPSCounter.h
//  HelloOpenCL
//
//  Created by Jack Armstrong on 6/24/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef FPSCounter_h
#define FPSCounter_h

#include <GLFW/glfw3.h>

class FPSCounter{
private:
    float timeStart;
    float frames;
    float fps;
    float diffTime;
public:
    FPSCounter(){
        
    };
    ~FPSCounter(){
        
    };
    void init(){
        timeStart=0;
        frames=0;
        fps=0;
    };
    void setDiffTime(float dt){
        diffTime=dt;
    };
    void update(){
        frames++;
        float time=glfwGetTime();
        if(time-timeStart>diffTime){
            fps=frames/(time-timeStart);
            timeStart=time;
            frames=0;
        }
    };
    float getFPS(){
        return fps;
    };
};


#endif /* FPSCounter_h */
