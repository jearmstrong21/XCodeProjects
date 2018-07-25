
float sq(float f);

float sq(float f){
    return f*f;
}

kernel void nbody(global float*x,global float*y,global float* z,global float*vx,global float*vy,global float* vz,global float*tracers, global float*mass,int num_particles,float dt,float G){
    int i=get_global_id(0);
    float fx=0,fy=0,fz=0;
    for(int j=0;j<num_particles;j++){
        if(i==j)continue;
        if(tracers[j])continue;
        float distSq=sq(x[i]-x[j])+sq(y[i]-y[j]);
        if(distSq<0.001f)continue;
        float mult=G*mass[j]*mass[i]/distSq;
        fx+=mult*(x[j]-x[i]);
        fy+=mult*(y[j]-y[i]);
        fz+=mult*(z[j]-z[i]);
    }
    vx[i]+=fx*dt/mass[i];
    vy[i]+=fy*dt/mass[i];
    vz[i]+=fz*dt/mass[i];
    x[i]+=vx[i]*dt;
    y[i]+=vy[i]*dt;
    z[i]+=vz[i]*dt;
}
