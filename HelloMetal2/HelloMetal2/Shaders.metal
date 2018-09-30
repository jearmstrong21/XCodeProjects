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
    float3 color;
    float2 uv;
};

vertex VertexToFragment basicVertex(const device packed_float3* posData [[ buffer(0) ]], const device packed_float3* colData [[ buffer(1) ]], const device packed_float2* uvData [[ buffer(2) ]], constant float4x4 &perspective [[ buffer(3) ]], constant float4x4 &modelView [[ buffer(4) ]], unsigned int vertexID [[ vertex_id ]]){
    VertexToFragment v2f;
    v2f.position = perspective*modelView*float4(posData[vertexID], 1.0);
    v2f.color = colData[vertexID];
    v2f.uv = uvData[vertexID];
    return v2f;
}

fragment float4 basicFragment(VertexToFragment v2f [[stage_in]], texture2d<float> theTexture [[ texture(0) ]], sampler theSampler [[ sampler(0) ]]) {
    
    float origX=4*v2f.uv.x-2;
    float origY=4*v2f.uv.y-2;
    float x=origX;
    float y=origY;
    int i;
    int m=20;
    for(i=0;i<m&&x*x+y*y<4;i++){
        float nx=x*x-y*y;
        float ny=2*x*y;
        x=nx+origX;
        y=ny+origY;
    }
    
    return (0.5+0.5*i/m)*float4(theTexture.sample(theSampler, v2f.uv).xyz * v2f.color, 1.0);
}
