//
//  Grid.hpp
//  StableFluidSimulation
//
//  Created by Jack Armstrong on 8/3/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <stdio.h>

#define GRIDSIZE 125

class Grid{
public:
    float data[GRIDSIZE][GRIDSIZE];
    
    void init(){
        for(int x=0;x<GRIDSIZE;x++){
            for(int y=0;y<GRIDSIZE;y++){
                data[x][y]=0;
            }
        }
    }
    
    Grid copy(){
        Grid g;
        g.init();
        for(int x=0;x<GRIDSIZE;x++){
            for(int y=0;y<GRIDSIZE;y++){
                g.data[x][y]=data[x][y];
            }
        }
        return g;
    }
    
    float operator () (int x, int y){
        while(x<0)x+=GRIDSIZE;
        while(y<0)y+=GRIDSIZE;
        while(x>=GRIDSIZE)x-=GRIDSIZE;
        while(y>=GRIDSIZE)y-=GRIDSIZE;
        return data[x][y];
    }
    
    void set(int x,int y,float f){
        while(x<0)x+=GRIDSIZE;
        while(y<0)y+=GRIDSIZE;
        while(x>=GRIDSIZE)x-=GRIDSIZE;
        while(y>=GRIDSIZE)y-=GRIDSIZE;
        data[x][y]=f;
    }
};

#endif /* Grid_hpp */
