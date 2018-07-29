
bool collidable(int x1,int y1,int x2,int y2);
int iabs(int i);

int iabs(int i){
    if(i<0)return -i;
    return i;
}

bool collidable(int x1,int y1,int x2,int y2){
    return iabs(x1-x2)<=1&&iabs(y1-y2)<=1;
}

kernel void ComputeGridPositions(global int*gx,global int*gy,global float*x,global float*y,global float*vx,global float*vy,global float*fx,global float*fy,global float*rho,global float*p,float G_x,float G_y,float REST_DENS,float GAS_CONST,float H,float HSQ,float MASS,float VISC,float DT,float POLY6,float SPIKY_GRAD,float VISC_LAP,float BOUND_SIZE,float BOUND_DAMPING,float SIM_W,float SIM_H,int num_particles){
    int i=get_global_id(0);
    gx[i]=(int)(x[i]/(SIM_W/H*2));
    gy[i]=(int)(y[i]/(SIM_H/H*2));
}

kernel void ComputeDensityPressure(global int*gx,global int*gy,global float*x,global float*y,global float*vx,global float*vy,global float*fx,global float*fy,global float*rho,global float*p,float G_x,float G_y,float REST_DENS,float GAS_CONST,float H,float HSQ,float MASS,float VISC,float DT,float POLY6,float SPIKY_GRAD,float VISC_LAP,float BOUND_SIZE,float BOUND_DAMPING,float SIM_W,float SIM_H,int num_particles){
    int i=get_global_id(0);
    rho[i]=0;
    for(int j=0;j<num_particles;j++){
        if(!collidable(gx[i],gy[i],gx[j],gy[j]))continue;
        float rij_x=x[j]-x[i];
        float rij_y=y[j]-y[i];
        float r2=rij_x*rij_x+rij_y*rij_y;
        if(r2<HSQ){
            rho[i]+=MASS*POLY6*pow(HSQ-r2,3.0f);
        }
    }
    p[i]=GAS_CONST*(rho[i]-REST_DENS);
}


kernel void ComputeForces(global int*gx,global int*gy,global float*x,global float*y,global float*vx,global float*vy,global float*fx,global float*fy,global float*rho,global float*p,float G_x,float G_y,float REST_DENS,float GAS_CONST,float H,float HSQ,float MASS,float VISC,float DT,float POLY6,float SPIKY_GRAD,float VISC_LAP,float BOUND_SIZE,float BOUND_DAMPING,float SIM_W,float SIM_H,int num_particles){
    int i=get_global_id(0);
    float press_x=0,press_y=0,visc_x=0,visc_y=0;
    
    for(int j=0;j<num_particles;j++){
        if(i==j)continue;
        if(!collidable(gx[i],gy[i],gx[j],gy[j]))continue;
        float rij_x=x[j]-x[i];
        float rij_y=y[j]-y[i];
        float r=sqrt(rij_x*rij_x+rij_y*rij_y);
        if(r<H){
            rij_x/=r;
            rij_y/=r;
            float press_mult=MASS*(p[i]+p[j])/(2*rho[j])*SPIKY_GRAD*pow(H-r,2.0f);
            float visc_mult=VISC*MASS/rho[j]*VISC_LAP*(H-r);
            press_x-=rij_x*press_mult;
            press_y-=rij_y*press_mult;
            visc_x+=visc_mult*(vx[j]-vx[i]);
            visc_y+=visc_mult*(vy[j]-vy[i]);
        }
    }
    
    fx[i]=G_x*rho[i]+press_x+visc_x;
    fy[i]=G_y*rho[i]+press_y+visc_y;
}


kernel void Integrate(global int*gx,global int*gy,global float*x,global float*y,global float*vx,global float*vy,global float*fx,global float*fy,global float*rho,global float*p,float G_x,float G_y,float REST_DENS,float GAS_CONST,float H,float HSQ,float MASS,float VISC,float DT,float POLY6,float SPIKY_GRAD,float VISC_LAP,float BOUND_SIZE,float BOUND_DAMPING,float SIM_W,float SIM_H,int num_particles){
    int i=get_global_id(0);
    vx[i]+=DT*fx[i]/rho[i];
    vy[i]+=DT*fy[i]/rho[i];
    x[i]+=DT*vx[i];
    y[i]+=DT*vy[i];
    if(x[i]<BOUND_SIZE){
        x[i]=BOUND_SIZE;
        vx[i]*=BOUND_DAMPING;
    }
    if(y[i]<BOUND_SIZE){
        y[i]=BOUND_SIZE;
        vy[i]*=BOUND_DAMPING;
    }
    if(x[i]>SIM_W-BOUND_SIZE){
        x[i]=SIM_W-BOUND_SIZE;
        vx[i]*=BOUND_DAMPING;
    }
    if(y[i]>SIM_H-BOUND_SIZE){
        y[i]=SIM_H-BOUND_SIZE;
        vy[i]*=BOUND_DAMPING;
    }
}
