#include <cstdlib>
#include <cmath>
#include "cl.hpp"
#include <OpenCL/cl.h>

#include <vector>
#include <string>

#include "DebugCL.hpp"

using std::vector;
using std::string;

using cl::Platform;
using cl::Device;
using cl::Context;
using cl::Program;
using cl::Buffer;
using cl::CommandQueue;
using cl::Kernel;
using cl::NDRange;
using cl::NullRange;

int main(){
    vector<Platform> platforms=printPlatformInfo();
    
    printf("\nGPUS: \n");
    
    vector<Device> gpus=printDeviceInfo(platforms[0], CL_DEVICE_TYPE_GPU);
    
    printf("\nCPUS: \n");
    
    vector<Device> cpus=printDeviceInfo(platforms[0], CL_DEVICE_TYPE_CPU);
    
    bool useGPU=true;
    int deviceInd=1;
    
    Device device;
    if(useGPU){
        device=gpus[deviceInd];
    }else{
        device=cpus[deviceInd];
    }
    
    Context ctx({device});
    
    string kernelCode=
    "kernel void mult(global int*a,global int*b,global int*c,int offset){"
    "   int i=get_global_id(0);"
    "   c[i]=a[i]*b[i]+offset;"
    "}";
    
    Program::Sources sources;
    sources.push_back({kernelCode.c_str(),kernelCode.length()});
    
    
    Program program(ctx,sources);
    if(program.build({device})!=CL_SUCCESS){
        printf("Error building:\n%s\n",program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device).c_str());
        return 1;
    }
    
    const int num=10;
    
    Buffer bufA(ctx,CL_MEM_READ_WRITE,sizeof(int)*num);
    Buffer bufB(ctx,CL_MEM_READ_WRITE,sizeof(int)*num);
    Buffer bufC(ctx,CL_MEM_READ_WRITE,sizeof(int)*num);

    CommandQueue cq(ctx,device);
    
    int dataA[num];
    int dataB[num];
    
    for(int i=0;i<num;i++){
        dataA[i]=i+1;
        dataB[i]=num-i;
    }
    
    cq.enqueueWriteBuffer(bufA, CL_TRUE, 0, sizeof(int)*num, dataA);
    cq.enqueueWriteBuffer(bufB, CL_TRUE, 0, sizeof(int)*num, dataB);
    cq.flush();
    
    Kernel kernel(program,"mult");
    
    int offset=4;
    
    kernel.setArg(0,bufA);
    kernel.setArg(1,bufB);
    kernel.setArg(2,bufC);
    kernel.setArg(3,offset);
    
    cq.enqueueNDRangeKernel(kernel, NullRange, NDRange(num));
    cq.flush();
    
    int dataC[num];
    cq.enqueueReadBuffer(bufC, CL_TRUE, 0, sizeof(int)*num, dataC);
    cq.flush();
    
    for(int i=0;i<num;i++){
//        if(dataA[i]*dataB[i]!=dataC[i])printf("%i x %i is not %i\n",dataA[i],dataB[i],dataC[i]);
        printf("%ix%i+%i=%i\n",dataA[i],dataB[i],offset, dataC[i]);
    }

    return 0;
}
