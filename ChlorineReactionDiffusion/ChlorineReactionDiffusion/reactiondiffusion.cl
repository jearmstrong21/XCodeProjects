
int ind(int x,int y,int SIMSIZE);

int ind(int x,int y,int SIMSIZE){
    if(x<0)x=SIMSIZE-1;
    else if(x>=SIMSIZE)x=0;
    if(y<0)y=SIMSIZE-1;
    else if(y>=SIMSIZE)x=0;
    
    return x+y*SIMSIZE;
}



kernel void reactiondiffusion(global float*gridA,global float*gridB,float Da,float Db,float paramF,float paramK,float dt,int SIMSIZE){
    int i=get_global_id(0);
    int x=i/SIMSIZE;
    int y=i%SIMSIZE;
//
//    float laplaceA=
//     0.05*gridA[ind(x-1,y-1,SIMSIZE)]+0.2*gridA[ind(x-1,y,SIMSIZE)]+0.05*gridA[ind(x-1,y+1,SIMSIZE)]
//    +0.2 *gridA[ind(x  ,y-1,SIMSIZE)]-    gridA[ind(x  ,y,SIMSIZE)]+0.05*gridA[ind(x  ,y+1,SIMSIZE)]
//    +0.05*gridA[ind(x+1,y-1,SIMSIZE)]+0.2*gridA[ind(x+1,y,SIMSIZE)]+0.05*gridA[ind(x+1,y+1,SIMSIZE)];
//    float laplaceB=
//     0.05*gridB[ind(x-1,y-1,SIMSIZE)]+0.2*gridB[ind(x-1,y,SIMSIZE)]+0.05*gridB[ind(x-1,y+1,SIMSIZE)]
//    +0.2 *gridB[ind(x  ,y-1,SIMSIZE)]-    gridB[ind(x  ,y,SIMSIZE)]+0.05*gridB[ind(x  ,y+1,SIMSIZE)]
//    +0.05*gridB[ind(x+1,y-1,SIMSIZE)]+0.2*gridB[ind(x+1,y,SIMSIZE)]+0.05*gridB[ind(x+1,y+1,SIMSIZE)];
//
//    float a=gridA[ind(x,y,SIMSIZE)];
//    float b=gridB[ind(x,y,SIMSIZE)];
//
//    float da=Da*laplaceA-a*b*b+paramF*(1-a);
//    float db=Db*laplaceB+a*b*b-(paramF+paramK)*b;
//
//    a+=da*dt;
//    b+=db*dt;
//
//    if(a<0)a=0;
//    if(b<0)b=0;
//    if(a>1)a=1;
//    if(b>1)b=1;
//
//    gridA[ind(x,y,SIMSIZE)]=a;
//    gridB[ind(x,y,SIMSIZE)]=b;
    
    gridB[ind(x,y,SIMSIZE)]+=0.01;
}
