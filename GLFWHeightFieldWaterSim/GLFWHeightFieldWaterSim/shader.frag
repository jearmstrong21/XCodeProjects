#version 330 core

flat in vec3 fragCol;
in vec2 fragUV;

out vec4 FragColor;


void main(){
    float f=fragCol.b;
    float stepped=smoothstep(0.0,1.0,f);
    vec4 start=vec4(0.0,0.93,1.0,1.0);
    vec4 end=vec4(0.0,0.64,0.85,1.0);
//    FragColor=mix(start,end,smoothstep(0.0,1.0,f));
    FragColor=vec4(vec3(smoothstep(0.0,1.0,f)),1.0);
//    if(fragUV.x<0.1||fragUV.y<0.1)FragColor=vec4(1.0);
}
