
__kernel void square(__global int* data){
    int i=get_global_id(0);
    data[i]=data[i]*data[i];
}
