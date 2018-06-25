

kernel void mult(global float* a, global float* b,global float* c){
    int id=get_global_id(0);
    c[id]=a[id]*b[id];
}

