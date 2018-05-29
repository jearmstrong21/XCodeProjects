
#version 330 core
layout (location = 0) in vec3 in_pos; //ALWAYS HAVE 'layout (location=0)'!!
//out vec4 outPos;
uniform float offX;
uniform float offY;
uniform float rot;

vec2 rotate(vec2 v, float a) {
    float s = sin(a);
    float c = cos(a);
    mat2 m = mat2(c, -s, s, c);
    return m * v;
}
void main() {
    vec2 newVec=rotate(in_pos.xy,rot);
    gl_Position=vec4(offX+newVec.x,offY+newVec.y,0.0,1.0);
}
