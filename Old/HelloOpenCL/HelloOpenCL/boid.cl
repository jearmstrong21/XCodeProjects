
constant float attractPosMult=0.009;
constant float attractPosDist=0.075*1.5;

constant float sepMult=0.2;
constant float sepDist=0.0158*1.5;

constant float attractVelMult=0.0075;
constant float attractVelDist=0.075*1.5;

constant float boundaryRepelMult=0.01;

#define PI 3.14159265359

kernel void boid(int num_boids,
                 int offset,
                 
                 global float* posBounds,
                 global float* velBounds,
                 
                 global float*inx,global float*iny,global float*invx,global float*invy,
                 global float*outx,global float*outy,global float*outvx,global float*outvy,global float*outang){
    int id=get_global_id(0);
    int in_ind=id+offset;
    float x=inx[in_ind];
    float y=iny[in_ind];
    float vx=invx[in_ind];
    float vy=invy[in_ind];

    float ax=0;
    float ay=0;
    
    float accAttractPosX=0,accAttractPosY=0;
    float accAttractPosNum=0;
    
    float sepX=0,sepY=0;
    float sepNum=0;
    
    float attrVelX=0,attrVelY=0;
    float attrVelNum=0;
    
    for(int i=0;i<num_boids;i++){
        float diffx=x-inx[i];
        float diffy=y-iny[i];
        float other_vx=invx[i];
        float other_vy=invy[i];
        float distsq=diffx*diffx+diffy*diffy;
        float dist=sqrt(distsq);
        //----- attract position -----
        if(dist<attractPosDist){
            accAttractPosX-=diffx;
            accAttractPosY-=diffy;
            accAttractPosNum++;
        }
        //----- seperate position -----
        if(dist<sepDist){
            sepX+=diffx;
            sepY+=diffy;
            sepNum++;
        }
        //----- attract velocity -----
        if(dist<attractVelDist){
            attrVelX+=other_vx;
            attrVelY+=other_vy;
            attrVelNum++;
        }
    }
    
    if(accAttractPosNum>0){
        accAttractPosX/=accAttractPosNum;
        accAttractPosY/=accAttractPosNum;
        ax+=accAttractPosX*attractPosMult;
        ay+=accAttractPosY*attractPosMult;
    }
    if(sepNum>0){
        sepX/=sepNum;
        sepY/=sepNum;
        ax+=sepX*sepMult;
        ay+=sepY*sepMult;
    }
    
    if(attrVelNum>0){
        attrVelX/=attrVelNum;
        attrVelY/=attrVelNum;
        ax+=attrVelX*attractVelMult;
        ay+=attrVelY*attractVelMult;
    }

    vx+=ax;
    vy+=ay;
    x+=vx;
    y+=vy;
    if(x<posBounds[0]){
        vx-=x*boundaryRepelMult;
//        x=posBounds[0];
    }
    if(y<posBounds[1]){
        vy-=y*boundaryRepelMult;
//        y=posBounds[1];
    }
    if(x>posBounds[2]){
        vx-=x*boundaryRepelMult;
//        x=posBounds[2];
    }
    if(y>posBounds[3]){
        vy-=y*boundaryRepelMult;
//        y=posBounds[3];
    }
    
    
    if(vx<velBounds[0])vx=velBounds[0];
    if(vy<velBounds[1])vy=velBounds[1];
    if(vx>velBounds[2])vx=velBounds[2];
    if(vy>velBounds[3])vy=velBounds[3];

    outx[id]=x;
    outy[id]=y;
    outvx[id]=vx;
    outvy[id]=vy;
    outang[id]=atan2(vy,vx)*180/PI-90;
    
//    //--------------------------------------------------------//
//    //Default kernel that passes data through without changing//
//    //--------------------------------------------------------//
//    int i=get_global_id(0);
//    outx[i]=inx[i+offset];
//    outy[i]=iny[i+offset];
//    outvx[i]=invx[i+offset];
//    outvy[i]=invy[i+offset];
//    outang[i]=0;
}
