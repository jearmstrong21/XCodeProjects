#version 330 core

out vec4 FragColor;

uniform float colR;
uniform float colG;
uniform float colB;

void main(){
    FragColor=vec4(colR,colG,colB,1.0);
}


