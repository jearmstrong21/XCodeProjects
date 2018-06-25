#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inCol;
layout (location = 2) in vec2 inUV;

//out vec4 vertPos;
flat out vec3 fragCol;
out vec2 fragUV;


void main(){
    gl_Position=vec4(inPos,1.0);
    fragCol=inCol;
    fragUV=inUV;
}
