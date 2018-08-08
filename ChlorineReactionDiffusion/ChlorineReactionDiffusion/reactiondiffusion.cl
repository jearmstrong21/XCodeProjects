
int ind(int x,int y,int SIMSIZE);
int ind(int x,int y,int SIMSIZE){
//    if(x<0)x=SIMSIZE-1;
//    else if(x>=SIMSIZE)x=0;
//    if(y<0)y=SIMSIZE-1;
//    else if(y>=SIMSIZE)x=0;
    while(x<0)x+=SIMSIZE;
    while(y<0)y+=SIMSIZE;
    while(x>=SIMSIZE)x-=SIMSIZE;
    while(y>=SIMSIZE)y-=SIMSIZE;
    
    return x+y*SIMSIZE;
}

float m_abs(float f);
float m_abs(float f){
    return f<0?-f:f;
}

kernel void reactiondiffusion(global float*gridA,global float*gridB,global float* newA,global float*newB,float Da,float Db,float paramF,float paramK,float dt,int SIMSIZE){
    int i=get_global_id(0);
    int x=i%SIMSIZE;
    int y=(i-x)/SIMSIZE;

    float laplaceA=0.05*(gridA[ind(x-1,y-1,SIMSIZE)]+gridA[ind(x+1,y-1,SIMSIZE)]+gridA[ind(x-1,y+1,SIMSIZE)]+gridA[ind(x+1,y+1,SIMSIZE)])
    +0.2*(gridA[ind(x,y-1,SIMSIZE)]+gridA[ind(x,y+1,SIMSIZE)]+gridA[ind(x-1,y,SIMSIZE)]+gridA[ind(x+1,y,SIMSIZE)])-gridA[ind(x,y,SIMSIZE)];
    float laplaceB=0.05*(gridB[ind(x-1,y-1,SIMSIZE)]+gridB[ind(x+1,y-1,SIMSIZE)]+gridB[ind(x-1,y+1,SIMSIZE)]+gridB[ind(x+1,y+1,SIMSIZE)])
    +0.2*(gridB[ind(x,y-1,SIMSIZE)]+gridB[ind(x,y+1,SIMSIZE)]+gridB[ind(x-1,y,SIMSIZE)]+gridB[ind(x+1,y,SIMSIZE)])-gridB[ind(x,y,SIMSIZE)];
    
    float a=gridA[ind(x,y,SIMSIZE)];
    float b=gridB[ind(x,y,SIMSIZE)];
    
    float na=a+(Da*laplaceA-a*b*b+paramF*(1-a))*dt;
    float nb=b+(Db*laplaceB+a*b*b-(paramK+paramF)*b)*dt;
    
    newA[i]=na;
    newB[i]=nb;
    
}

kernel void swap(global float*gridA,global float*gridB,global float*newA,global float*newB){
    int i=get_global_id(0);
    gridA[i]=newA[i];
    gridB[i]=newB[i];
}
