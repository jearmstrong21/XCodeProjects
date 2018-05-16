#version 330 core
out vec4 FragColor;

uniform bool doMandelbrot;
uniform float xOffScale;
uniform float yOffScale;
uniform float maxIters;
uniform bool doHSB;

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
        if(doMandelbrot){
            x=newX+origX*xOffScale;
            y=newY+origY*yOffScale;
        }else{
            x=newX+xOffScale;
            y=newY+yOffScale;
        }
        i+=1.0;
    }
    if(doHSB)FragColor=vec4(hsv2rgb(vec3(i/maxIters,0.75,1.0)),1.0);
    else FragColor=vec4(i/maxIters,i/maxIters,i/maxIters,1.0);
}
