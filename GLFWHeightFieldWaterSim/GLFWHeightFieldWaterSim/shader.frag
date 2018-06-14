#version 330 core

flat in vec3 fragCol;

out vec4 FragColor;


void main(){
    float f=fragCol.b;
    vec4 start=vec4(0.0,0.93,1.0,1.0);
    vec4 end=vec4(0.0,0.64,0.85,1.0);
    FragColor=mix(start,end,smoothstep(0.0,1.0,f));
}
