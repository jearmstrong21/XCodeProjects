#version 330 core
out vec4 FragColor;

uniform int fractalType;
uniform float xOffScale;
uniform float yOffScale;
uniform float maxIters;
uniform bool doHSB;
uniform bool doSmooth;

#define PI 3.1415926535897932384626433832795

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}
void main()
{
//    int fractalType=0;
//    float xOffScale=1;
//    float yOffScale=1;
//    float maxIters=50;
//    bool doHSB=false;
//    bool doSmooth=true;
    
    vec3 coord=gl_FragCoord.xyz/1000.0;
    float origX=2.0*(coord.x-1);
    float origY=2.0*(coord.y-1);
    float x=origX;
    float y=origY;
    float newX;
    float newY;
    float i=0.0;
    while(i<maxIters-1&&x*x+y*y<1600){
        newX=x*x-y*y;
        newY=2.0*x*y;
        if(fractalType==0){
            x=newX+origX*xOffScale;
            y=newY+origY*yOffScale;
        }else if(fractalType==1){
            x=newX+xOffScale;
            y=newY+yOffScale;
        }
        i+=1;
    }
    if(doSmooth){
        float nsmooth = 1.0 - log(0.0001+log(0.0001+sqrt(x*x+y*y)))/log(2.0);
        i += nsmooth;
    }
    //    i=round(i/30.0)*30;
    if(doHSB)FragColor=vec4(hsv2rgb(vec3(i/maxIters,0.5,1.0)),1.0);
    else FragColor=vec4(i/maxIters,i/maxIters,i/maxIters,1.0);
//    FragColor=vec4(gl_FragCoord.xyz/1000.0,1.0);
//    FragColor=vec4(fractalType,fractalType,fractalType,1.0);
    //    if(i<maxIters)FragColor=vec4(0.0,0.0,0.0,0.0);
//    float fx=gl_FragCoord.x/1000.0;
//    float fy=gl_FragCoord.y/1000.0;
//    fx=fract(fx*100.0);
//    fy=fract(fy*100.0);
//    if(fx<0.1||fy<0.1)FragColor=vec4(1.0-FragColor.x,1.0-FragColor.y,1.0-FragColor.z,1.0);;
//    if(abs(origX)<0.01||abs(origY)<0.01)FragColor=vec4(1.0,1.0,1.0,1.0);

}


