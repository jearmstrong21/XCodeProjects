//
//  Update.hpp
//  StableFluidSimulation
//
//  Created by Jack Armstrong on 8/3/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef Update_hpp
#define Update_hpp

#include <stdlib.h>
#include "Grid.hpp"

const float dt=1;
const int PRESSURE_SOLVE_ITERS=80;
const bool DO_DIFFUSE=false;

void diffuse(Grid &from, Grid &to){
    for(int x=0;x<GRIDSIZE;x++){
        for(int y=0;y<GRIDSIZE;y++){
            to.set(x,y,  (from(x,y)+dt*(from(x-1,y)+from(x+1,y)+from(x,y-1)+from(x,y+1)))/(1+4*dt)    );
        }
    }
}

void advect(Grid &from, Grid &to, Grid &vx, Grid &vy){
    for(int i=1;i<GRIDSIZE-1;i++){
        for(int j=1;j<GRIDSIZE-1;j++){
            float x=i-dt*vx(i, j);
            float y=j-dt*vy(i, j);
            int i0=floor(x);
            int j0=floor(y);
            int i1=i0+1;
            int j1=j0+1;
            float s1=x-i0;
            float s0=1-s1;
            float t1=y-j0;
            float t0=1-t1;
            to.data[i][j]=s0*(t0*from(i0, j0)+t1*from(i0, j1))+
            s1*(t0*from(i1, j0)+t1*from(i1, j1));
        }
    }
}

void calcDivergence(Grid &density, Grid &divergence, Grid &vx, Grid &vy){
    for(int x=1;x<GRIDSIZE-1;x++){
        for(int y=1;y<GRIDSIZE-1;y++){
            divergence.set(x,y,  (-2/dt)*(vx(x+1,y)-vx(x-1,y)+vy(x,y+1)-vy(x,y-1))   );
        }
    }
}

void solvePressure(Grid &divergence, Grid &pressure){
    pressure.init();//set to 0
    Grid pressure0=pressure.copy();
    for(int i=0;i<PRESSURE_SOLVE_ITERS;i++){
        
        for(int x=1;x<GRIDSIZE-1;x++){
            for(int y=1;y<GRIDSIZE-1;y++){
                pressure.set(x,y,  (divergence(x,y)+pressure0(x-2,y)+pressure0(x+2,y)+pressure0(x,y-2)+pressure0(x,y+2))/4.0f   );
            }
        }
        
        pressure0=pressure.copy();
        
    }
}

void fixDivergence(Grid &pressure, Grid&vx, Grid &vy){
    for(int x=1;x<GRIDSIZE-1;x++){
        for(int y=1;y<GRIDSIZE-1;y++){
            float gradX=dt*0.5*(pressure(x+1,y)-pressure(x-1,y));
            float gradY=dt*0.5*(pressure(x,y+1)-pressure(x,y-1));
//            printf("%f,%f\n",gradX,gradY);//why is this zero?  solvePressure must be broken, check swap code
            vx.set(x,y,  vx(x,y)-gradX);
            vy.set(x,y,  vy(x,y)-gradY);
        }
    }
}

float pressureAccuracy(Grid &divergence, Grid &pressure){
    float f=0;
    for(int x=1;x<GRIDSIZE-1;x++){
        for(int y=1;y<GRIDSIZE-1;y++){
            float realValue=4*pressure(x,y)-pressure(x-1,y)-pressure(x+1,y)-pressure(x,y-1)-pressure(x,y+1);
            f+=abs(realValue-divergence(x,y));
        }
    }
    return f/(GRIDSIZE-2)/(GRIDSIZE-2);
}

float avg(Grid &g){
    float f=0;
    for(int x=1;x<GRIDSIZE-1;x++){
        for(int y=1;y<GRIDSIZE-1;y++){
            f+=g(x,y);
        }
    }
    return f/(GRIDSIZE-2)/(GRIDSIZE-2);
}

void bndVel(Grid &vx,Grid &vy){
    float f=1.0;
    for(int i=0;i<GRIDSIZE;i++){
        vx.data[i][0]=0;
        vy.data[i][0]=-f*vy.data[i][1];
        
        vx.data[i][GRIDSIZE-1]=0;
        vy.data[i][GRIDSIZE-1]=-f*vy.data[i][GRIDSIZE-2];
        
        vx.data[0][i]=-f*vx.data[1][i];
        vy.data[0][i]=0;
        
        vx.data[GRIDSIZE-1][i]=-f*vx.data[GRIDSIZE-2][i];
        vy.data[GRIDSIZE-1][i]=0;
    }
}

void bndField(Grid &g){
    for(int i=0;i<GRIDSIZE;i++){
//        g.data[i][0]=g.data[0][i]=g.data[i][GRIDSIZE-1]=g.data[GRIDSIZE-1][i]=0;
        g.data[i][1]+=g.data[i][0];g.data[i][0]=0;
        g.data[1][i]+=g.data[0][i];g.data[0][i]=0;
        g.data[i][GRIDSIZE-2]+=g.data[i][GRIDSIZE-1];g.data[i][GRIDSIZE-1]=0;
        g.data[GRIDSIZE-2][i]+=g.data[GRIDSIZE-1][i];g.data[GRIDSIZE-1][i]=0;
    }
}

void update(Grid &vx, Grid &vy, Grid &density, Grid &pressure, Grid &divergence){
    
//    for(int x=0;x<GRIDSIZE;x++){
//        for(int y=0;y<GRIDSIZE;y++){
//            vy.data[x][y]-=0.001;
//        }
//    }
    bndVel(vx,vy);
//    bndField(density);
    
    
    Grid density0=density.copy();
    advect(density0,density,vx,vy);
    bndVel(vx,vy);
//    bndField(density);
    
    Grid vx0=vx.copy();
    Grid vy0=vy.copy();
    
    advect(vx0,vx,vx0,vy0);
    bndVel(vx,vy);
//    bndField(density);
    
    advect(vy0,vy,vx0,vy0);
    bndVel(vx,vy);
//    bndField(density);
    
    calcDivergence(density, divergence, vx, vy);
    bndVel(vx,vy);
//    bndField(density);

    solvePressure(divergence, pressure);
    bndVel(vx,vy);
//    bndField(density);

    fixDivergence(pressure, vx, vy);
    bndVel(vx,vy);
//    bndField(density);


//    printf("Pressure solver accuracy: %f\n",pressureAccuracy(divergence, pressure));
    printf("Density average: %f\n", avg(density));
    
}








#endif /* Update_hpp */
