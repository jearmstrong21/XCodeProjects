
#version 330 core
out vec4 FragColor;
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
    float maxIters=10.0;
    while(i<maxIters&&x*x+y*y<4){
        newX=x*x-y*y;
        newY=2.0*x*y;
        x=newX+0.8;
        y=newY+0.8;
        i+=1.0;
    }
//    FragColor=vec4(i/maxIters,i/maxIters,i/maxIters,1.0);
    FragColor=vec4(hsv2rgb(vec3(i/maxIters,1.0,1.0),1.0);
//    FragColor=vec4(origX,origY,0.0,1.0);
//    FragColor = vec4(gl_FragCoord.xyz/1000.0,1.0);
}
