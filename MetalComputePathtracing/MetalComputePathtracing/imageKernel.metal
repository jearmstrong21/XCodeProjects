//
//  grayscaleKernel.metal
//  MetalComputePathtracing
//
//  Created by Jack Armstrong on 10/21/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <metal_stdlib>
using namespace metal;

constant float3 kRec709Luma = float3(0.2126, 0.7152, 0.0722);

float gray(float4 p){
    return dot(p.rgb,kRec709Luma);
}

constant float sobelX[3][3]={
    {1,0,-1},
    {2,0,-2},
    {1,0,-1}
};
constant float sobelY[3][3]={
    {1,2,1},
    {0,0,0},
    {-1,-2,-1}
};

kernel void imageKernel(texture2d<float, access::read>     inTexture   [[texture(0)]],
                            texture2d<float, access::write>    outTexture  [[texture(1)]],
                            uint2                               gid         [[thread_position_in_grid]]
                            ){
    if((gid.x >= outTexture.get_width()) || (gid.y >= outTexture.get_height()))
    {
        // Return early if the pixel is out of bounds
        return;
    }

//    float4 p_00=inTexture.read(gid+uint2(-1,-1));
//    float4 p_01=inTexture.read(gid+uint2(-1, 0));
//    float4 p_02=inTexture.read(gid+uint2(-1, 1));
//    float4 p_10=inTexture.read(gid+uint2( 0,-1));
//    float4 p_11=inTexture.read(gid+uint2( 0, 0));
//    float4 p_12=inTexture.read(gid+uint2( 0, 1));
//    float4 p_20=inTexture.read(gid+uint2( 1,-1));
//    float4 p_21=inTexture.read(gid+uint2( 1, 0));
//    float4 p_22=inTexture.read(gid+uint2( 1, 1));
//    float _00=gray(p_00);
//    float _01=gray(p_01);
//    float _02=gray(p_02);
//    float _10=gray(p_10);
//    float _11=gray(p_11);
//    float _12=gray(p_12);
//    float _20=gray(p_20);
//    float _21=gray(p_21);
//    float _22=gray(p_22);
    float gX=0;
    float gY=0;
    for(int x=0;x<3;x++){
        for(int y=0;y<3;y++){
            float4 pixel=inTexture.read(gid+uint2(x-1,y-1));
            gX+=sobelX[x][y]*gray(pixel);
            gY+=sobelY[x][y]*gray(pixel);
        }
    }
    outTexture.write(float4(gX,gY,sqrt(gX*gX+gY*gY),1),gid);
//    float gray=1-sqrt(gX*gX+gY*gY);
//    if(gray<.5)gray=0;
//    else gray=1;
//    outTexture.write(gray*inTexture.read(gid), gid);
}
