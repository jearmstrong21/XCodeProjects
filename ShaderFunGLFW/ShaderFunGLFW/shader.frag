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
    vec3 coord=gl_FragCoord.xyz/1000.0;
    float origX=2.0*(coord.x-1);
    float origY=2.0*(coord.y-1);
    float x=origX;
    float y=origY;
    float newX;
    float newY;
    float i=0.0;
    while(i<maxIters&&x*x+y*y<1600){
        newX=x*x-y*y;
        newY=2.0*x*y;
        if(fractalType==0){
            x=newX+origX*1.0;
            y=newY+origY*1.0;
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
    if(doHSB)FragColor=vec4(hsv2rgb(vec3(i/maxIters,0.75,1.0)),1.0);
    else FragColor=vec4(i/maxIters,i/maxIters,i/maxIters,1.0);
//    if(i<maxIters)FragColor=vec4(0.0,0.0,0.0,0.0);å
    
}


