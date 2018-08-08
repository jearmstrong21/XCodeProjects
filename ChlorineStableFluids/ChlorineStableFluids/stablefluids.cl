
int ind(int x,int y,int SIMSIZE);
int ind(int x,int y,int SIMSIZE){
    while(x<0)x+=SIMSIZE;
    while(y<0)y+=SIMSIZE;
    while(x>=SIMSIZE)x-=SIMSIZE;
    while(y>=SIMSIZE)y-=SIMSIZE;
    return x+y*SIMSIZE;
}

bool in_bounds(int x,int y,int SIMSIZE);
bool in_bounds(int x,int y,int SIMSIZE){
    return x>0&&y>0&&x<SIMSIZE-1&&y<SIMSIZE-1;
}

kernel void transfer(global float*from,global float*to){
    int i=get_global_id(0);
    to[i]=from[i];
}

kernel void advect(global float*from, global float*to, global float*vx,global float*vy,float dt,int SIMSIZE){
    int id=get_global_id(0);
    int i=id%SIMSIZE;
    int j=id/SIMSIZE;
    if(!in_bounds(i,j,SIMSIZE))return;
    float x=i-dt*vx[ind(i,j,SIMSIZE)];
    float y=j-dt*vy[ind(i,j,SIMSIZE)];
    float i0=floor(x);
    float j0=floor(y);
    float i1=i0+1;
    float j1=j0+1;
    float s1=x-i0;
    float s0=1-s1;
    float t1=y-j0;
    float t0=1-t1;
    to[id]=s0*(t0*from[ind(i0,j0,SIMSIZE)]+t1*from[ind(i0,j1,SIMSIZE)])+s1*(t0*from[ind(i1,j0,SIMSIZE)]+t1*from[ind(i1,j1,SIMSIZE)]);
//    to[i]=from[i];
//    to[id]=0;
}

kernel void set_bounds(global float* vx,global float*vy,float boundVelMult,int SIMSIZE){
    int id=get_global_id(0);
    int x=id%SIMSIZE;
    int y=id/SIMSIZE;
    if(in_bounds(x,y,SIMSIZE))return;
    if(x==0){
        vx[ind(0,y,SIMSIZE)]=-boundVelMult*vx[ind(1,y,SIMSIZE)];
        vy[ind(0,y,SIMSIZE)]=0;
    }else if(y==0){
        vx[ind(x,0,SIMSIZE)]=0;
        vy[ind(x,0,SIMSIZE)]=-boundVelMult*vy[ind(x,1,SIMSIZE)];
    }else if(x==SIMSIZE-1){
        vx[ind(SIMSIZE-1,y,SIMSIZE)]=-boundVelMult*vx[ind(SIMSIZE-2,y,SIMSIZE)];
        vy[ind(SIMSIZE-1,y,SIMSIZE)]=0;
    }else if(y==SIMSIZE-1){
        vx[ind(x,SIMSIZE-1,SIMSIZE)]=0;
        vy[ind(x,SIMSIZE-1,SIMSIZE)]=-boundVelMult*vy[ind(x,SIMSIZE-2,SIMSIZE)];
    }
}

kernel void calc_divergence(global float* divergence, global float* density, global float* vx,global float* vy,float dt,int SIMSIZE){
    int id=get_global_id(0);
    int x=id%SIMSIZE;
    int y=id/SIMSIZE;
    if(!in_bounds(x,y,SIMSIZE))return;
    divergence[id]=(-2/dt)*(vx[ind(x+1,y,SIMSIZE)]-vx[ind(x-1,y,SIMSIZE)]+vy[ind(x,y+1,SIMSIZE)]-vy[ind(x,y-1,SIMSIZE)]);
}

kernel void solve_pressure(global float* pressure0, global float* pressure, global float* divergence,int SIMSIZE){
    int id=get_global_id(0);
    int x=id%SIMSIZE;
    int y=id/SIMSIZE;
    if(!in_bounds(x,y,SIMSIZE))return;
    pressure[id]=(divergence[id]+pressure0[ind(x-2,y,SIMSIZE)]+pressure0[ind(x+2,y,SIMSIZE)]+pressure0[ind(x,y-2,SIMSIZE)]+pressure0[ind(x,y+2,SIMSIZE)])/4;
}

kernel void correct_divergence(global float*pressure,global float*vx,global float*vy,float dt,int SIMSIZE){
    int id=get_global_id(0);
    int x=id%SIMSIZE;
    int y=id/SIMSIZE;
    if(!in_bounds(x,y,SIMSIZE))return;
    float gradX=dt*0.5*(pressure[ind(x+1,y,SIMSIZE)]-pressure[ind(x-1,y,SIMSIZE)]);
    float gradY=dt*0.5*(pressure[ind(x,y+1,SIMSIZE)]-pressure[ind(x,y-1,SIMSIZE)]);
    vx[id]-=gradX;
    vy[id]-=gradY;
}
