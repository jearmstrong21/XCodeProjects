////const static Vector2d G(0.f, 12000*-9.8f); // external (gravitational) forces
//constant float G_x=0;
//constant float G_y=-9.8*12000;
//constant float REST_DENS = 1000.f; // rest density
//constant float GAS_CONST = 2000.f; // const for equation of state
//constant float H = 16.f; // kernel radius
//constant float HSQ = 256/*H*H*/; // radius^2 for optimization
//constant float MASS = 65.f; // assume all particles have the same mass
//constant float VISC = 250.f; // viscosity constant
//constant float DT = 0.0008f; // integration timestep
//
//// smoothing kernels defined in Müller and their gradients
//constant float POLY6 = 2.244747417E-11/*315.f/(65.f*M_PI*pow(H, 9.f))*/;
//constant float SPIKY_GRAD = -8.537736E-7/*-45.f/(M_PI*pow(H, 6.f))*/;
//constant float VISC_LAP =8.537736E-7 /*45.f/(M_PI*pow(H, 6.f))*/;
//
//// simulation parameters
//constant float EPS = 16/*H*/; // boundary epsilon
//constant float BOUND_DAMPING = -0.5f;
//
//constant float VIEW_SIZE=800;

kernel void compute_density_pressure(int num_particles,
                                     int offset,
                                     global float* params,
                                     global float* inx,global float* iny,global float* invx,global float* invy,global float* infx,global float* infy,global float* inrho,global float* inp,
                                     global float*outx,global float*outy,global float*outvx,global float*outvy,global float*outfx,global float*outfy,global float*outrho,global float*outp){
    int outid=get_global_id(0);
    int inid=outid+offset;
    
    float G_x=params[0];
    float G_y=params[1];
    float REST_DENS=params[2];
    float GAS_CONST=params[3];
    float H=params[4];
    float HSQ=params[5];
    float MASS=params[6];
    float VISC=params[7];
    float DT=params[8];
    float POLY6=params[9];
    float SPIKY_GRAD=params[10];
    float VISC_LAP=params[11];
    float EPS=params[12];
    float BOUND_DAMPING=params[13];
    float VIEW_SIZE=params[14];
    
    float x=inx[inid];
    float y=iny[inid];
    float vx=invx[inid];
    float vy=invy[inid];
    float fx=infx[inid];
    float fy=infy[inid];
    float rho=inrho[inid];
    float p=inp[inid];
    

    
    rho=0;
    for(int j=0;j<num_particles;j++){
        float2 rij=float2(inx[j]-x,iny[j]-y);
        float r2=dot(rij,rij);
        if(r2<HSQ){
            rho+=MASS*POLY6*pow(HSQ-r2,3.0f);
        }
    }
    p=GAS_CONST*(rho-REST_DENS);
    
    
    
    
    
    outx[outid]=x;
    outy[outid]=y;
    outvx[outid]=vx;
    outvy[outid]=vy;
    outfx[outid]=fx;
    outfy[outid]=fy;
    outrho[outid]=rho;
    outp[outid]=p;
}

kernel void compute_forces(int num_particles,
                           int offset,
                           global float* params,
                           global float* inx,global float* iny,global float* invx,global float* invy,global float* infx,global float* infy,global float* inrho,global float* inp,
                           global float*outx,global float*outy,global float*outvx,global float*outvy,global float*outfx,global float*outfy,global float*outrho,global float*outp){
    int outid=get_global_id(0);
    int inid=outid+offset;
    
    float G_x=params[0];
    float G_y=params[1];
    float REST_DENS=params[2];
    float GAS_CONST=params[3];
    float H=params[4];
    float HSQ=params[5];
    float MASS=params[6];
    float VISC=params[7];
    float DT=params[8];
    float POLY6=params[9];
    float SPIKY_GRAD=params[10];
    float VISC_LAP=params[11];
    float EPS=params[12];
    float BOUND_DAMPING=params[13];
    float VIEW_SIZE=params[14];
    
    float x=inx[inid];
    float y=iny[inid];
    float vx=invx[inid];
    float vy=invy[inid];
    float fx=infx[inid];
    float fy=infy[inid];
    float rho=inrho[inid];
    float p=inp[inid];
    
    
    
    float2 fpress=float2(0,0);
    float2 fvisc=float2(0,0);
    float2 fgrav=rho*float2(G_x,G_y);
    
    for(int j=0;j<num_particles;j++){
        if(j==inid)continue;
        float2 rij=float2(inx[j]-x,iny[j]-y);
        float r=sqrt(dot(rij,rij));
        if(r<H){
            float2 diff_v=float2(invx[j]-vx,invy[j]-vy);
            fpress-=normalize(rij)*MASS*(p+inp[j])/(2*inrho[j])*SPIKY_GRAD*pow(H-r,2.0f);
            fvisc+=VISC*MASS*(diff_v)/inrho[j]*VISC_LAP*(H-r);
        }
    }
    
    float2 f=fpress+fvisc+fgrav;
    fx=f.x;
    fy=f.y;
    
    
    outx[outid]=x;
    outy[outid]=y;
    outvx[outid]=vx;
    outvy[outid]=vy;
    outfx[outid]=fx;
    outfy[outid]=fy;
    outrho[outid]=rho;
    outp[outid]=p;
}

kernel void integrate(int num_particles,
                      int offset,
                      global float* params,
                      global float* inx,global float* iny,global float* invx,global float* invy,global float* infx,global float* infy,global float* inrho,global float* inp,
                      global float*outx,global float*outy,global float*outvx,global float*outvy,global float*outfx,global float*outfy,global float*outrho,global float*outp){
    int outid=get_global_id(0);
    int inid=outid+offset;
    
    float G_x=params[0];
    float G_y=params[1];
    float REST_DENS=params[2];
    float GAS_CONST=params[3];
    float H=params[4];
    float HSQ=params[5];
    float MASS=params[6];
    float VISC=params[7];
    float DT=params[8];
    float POLY6=params[9];
    float SPIKY_GRAD=params[10];
    float VISC_LAP=params[11];
    float EPS=params[12];
    float BOUND_DAMPING=params[13];
    float VIEW_SIZE=params[14];
    
    float x=inx[inid];
    float y=iny[inid];
    float vx=invx[inid];
    float vy=invy[inid];
    float fx=infx[inid];
    float fy=infy[inid];
    float rho=inrho[inid];
    float p=inp[inid];
    
    vx+=DT*fx;
    vy+=DT*fy;
    x+=DT*vx;
    y+=DT*vy;
    
    if(x-EPS<0){
        vx*=BOUND_DAMPING;
        x=EPS;
    }
    if(y-EPS<0){
        vy*=BOUND_DAMPING;
        y=EPS;
    }
    if(x+EPS>VIEW_SIZE){
        vx*=BOUND_DAMPING;
        x=VIEW_SIZE-EPS;
    }
    if(y+EPS>VIEW_SIZE){
        vy*=BOUND_DAMPING;
        y=VIEW_SIZE-EPS;
    }
    
    outx[outid]=x;
    outy[outid]=y;
    outvx[outid]=vx;
    outvy[outid]=vy;
    outfx[outid]=fx;
    outfy[outid]=fy;
    outrho[outid]=rho;
    outp[outid]=p;
}
