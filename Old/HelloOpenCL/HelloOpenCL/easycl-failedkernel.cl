
constant float attractPosMult=0.001;
constant float attractPosDist=0.01;

constant float boundaryRepelMult=0.01;

kernel void boid(int num_boids,
                 int offset,
                 
                 global float* posBounds,
                 
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
    
    for(int i=0;i<num_boids;i++){
        float diffx=x-inx[i];
        float diffy=y-iny[i];
        float distsq=diffx*diffx+diffy*diffy;
        //----- attractPosMult -----
        if(distsq<attractPosDist){
            ax+=diffx*attractPosMult;
            ay+=diffy*attractPosMult;
        }
    }
    

    vx+=ax;
    vy+=ay;
    x+=vx;
    y+=vy;
    
    if(x<posBounds[0]){
        vx-=x*boundaryRepelMult;
    }
    if(y<posBounds[1]){
        vy-=y*boundaryRepelMult;
    }
    if(x>posBounds[2]){
        vx-=x*boundaryRepelMult;
    }
    if(y>posBounds[3]){
        vy-=y*boundaryRepelMult;
    }

    outx[id]=x;
    outy[id]=y;
    outvx[id]=vx;
    outvy[id]=vy;
    outang[id]=atan2(vy,vx);
    
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

