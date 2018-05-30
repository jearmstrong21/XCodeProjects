
#version 330 core
layout (location = 0) in vec3 in_pos; //ALWAYS HAVE 'layout (location=0)'!!
layout (location = 1) in vec2 in_tex_coord;

out vec2 fragTexCoord;

void main() {
    gl_Position=vec4(in_pos.xyz,1.0);
    fragTexCoord=in_tex_coord;
}

