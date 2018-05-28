
#version 330 core
layout (location = 0) in vec3 aPos; //ALWAYS HAVE 'layout (location=0)'!!
//out vec4 outPos;
//uniform mat4x4 ViewMatrix;
void main() {
    gl_Position=vec4(aPos.xyz,1.0);
}
