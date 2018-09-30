//
//  Kernel.metal
//  HelloMetalCompute
//
//  Created by Jack Armstrong on 9/30/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <metal_stdlib>
using namespace metal;

kernel void kernelFunction(const device int* array1 [[ buffer(0) ]], const device int* array2 [[ buffer(1) ]], device int* array3 [[ buffer(2) ]],
                           const uint tgPos [[ threadgroup_position_in_grid ]],
                           const uint tPerTg [[ threads_per_threadgroup ]],
                           const uint tPos [[ thread_position_in_threadgroup ]]){
    uint index = tgPos * tPerTg + tPos;
    array3[index] = array1[index] * array2[index];
}

