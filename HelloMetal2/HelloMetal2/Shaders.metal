//
//  Shaders.metal
//  HelloMetal2
//
//  Created by Jack Armstrong on 9/29/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <metal_stdlib>
using namespace metal;

struct VertexToFragment {
    float4 position [[ position ]];
    float4 color;
};

vertex VertexToFragment basicVertex(const device packed_float3* posData [[ buffer(0) ]], const device packed_float3* colData [[ buffer(1) ]], unsigned int vertexID [[ vertex_id ]]){
    VertexToFragment v2f;
    v2f.position = float4(posData[vertexID], 1.0);
    v2f.color = float4(colData[vertexID], 1.0);
    return v2f;
}

fragment half4 basicFragment(VertexToFragment v2f [[stage_in]]) {
    return half4(v2f.color);
}
