
kernel void compute_density_pressure(int num_particles,
                                     int offset,
                                     global float* inx,global float* iny,global float* invx,global float* invy,global float* infx,global float* infy,global float* inrho,global float* inp,
                                     global float*outx,global float*outy,global float*outvx,global float*outvy,global float*outfx,global float*outfy,global float*outrho,global float*outp){
    int outid=get_global_id(0);
    int inid=outid+offset;
    
    outx[outid]=inx[inid];
    outy[outid]=iny[inid];
    outvx[outid]=invx[inid];
    outvy[outid]=invy[inid];
    outfx[outid]=infx[inid];
    outfy[outid]=infy[inid];
    outrho[outid]=inrho[inid];
    outp[outid]=inp[inid];
}

kernel void compute_forces(int num_particles,
                           int offset,
                           global float* inx,global float* iny,global float* invx,global float* invy,global float* infx,global float* infy,global float* inrho,global float* inp,
                           global float*outx,global float*outy,global float*outvx,global float*outvy,global float*outfx,global float*outfy,global float*outrho,global float*outp){
    int outid=get_global_id(0);
    int inid=outid+offset;
    
    outx[outid]=inx[inid];
    outy[outid]=iny[inid];
    outvx[outid]=invx[inid];
    outvy[outid]=invy[inid];
    outfx[outid]=infx[inid];
    outfy[outid]=infy[inid];
    outrho[outid]=inrho[inid];
    outp[outid]=inp[inid];
}

kernel void integrate(int num_particles,
                      int offset,
                      global float* inx,global float* iny,global float* invx,global float* invy,global float* infx,global float* infy,global float* inrho,global float* inp,
                      global float*outx,global float*outy,global float*outvx,global float*outvy,global float*outfx,global float*outfy,global float*outrho,global float*outp){
    int outid=get_global_id(0);
    int inid=outid+offset;
    
    outx[outid]=inx[inid];
    outy[outid]=iny[inid];
    outvx[outid]=invx[inid];
    outvy[outid]=invy[inid];
    outfx[outid]=infx[inid];
    outfy[outid]=infy[inid];
    outrho[outid]=inrho[inid];
    outp[outid]=inp[inid];
}

