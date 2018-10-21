//
//  testKernel.metal
//  MetalComputePathtracing
//
//  Created by Jack Armstrong on 10/21/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <metal_stdlib>
using namespace metal;

kernel void testKernel(device int* a [[buffer(0)]], device int* b [[buffer(1)]], device int* c [[buffer(2)]],
                       const uint tgPos [[ threadgroup_position_in_grid ]],
                       const uint tPerTg [[ threads_per_threadgroup ]],
                       const uint tPos [[ thread_position_in_threadgroup ]]){
    uint index = tgPos * tPerTg + tPos;
    c[index]=a[index]*b[index];
}
