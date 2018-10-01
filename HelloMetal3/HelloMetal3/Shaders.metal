

#include <metal_stdlib>
using namespace metal;

struct VertexToFragment {
    float4 position [[ position ]];
    float3 color;
    float2 uv;
};

vertex VertexToFragment basicVertex(const device packed_float3* posData [[ buffer(0) ]], const device packed_float3* colData [[ buffer(1) ]], const device packed_float2* uvData [[ buffer(2) ]], unsigned int vertexID [[ vertex_id ]]){
    VertexToFragment v2f;
    v2f.position = float4(posData[vertexID], 1.0);
    v2f.color = colData[vertexID];
    v2f.uv = uvData[vertexID];
    return v2f;
}

fragment float4 basicFragment(VertexToFragment v2f [[stage_in]], texture2d<float> theTexture [[ texture(0) ]], sampler theSampler [[ sampler(0) ]],
                              const device float& xMult [[ buffer(0) ]],
                              const device float& yMult [[ buffer(1) ]],
                              const device float& xOff [[ buffer(2) ]],
                              const device float& yOff [[ buffer(3) ]]) {
    
    if(v2f.uv.x==-500&&v2f.uv.y==-500)return float4(v2f.color,1);
    
    float origX=4*v2f.uv.x-2;
    float origY=4*v2f.uv.y-2;
    float x=origX;
    float y=origY;
    int i;
    int m=20;
    for(i=0;i<m&&x*x+y*y<4;i++){
        float nx=x*x-y*y;
        float ny=2*x*y;
        x=nx+origX*xMult+xOff;
        y=ny+origY*yMult+yOff;
    }
    
    return float4(0.2+0.8*i/m);
}
