
#version 330 core
layout (location = 0) in vec3 in_pos; //ALWAYS HAVE 'layout (location=0)'!!
layout (location = 1) in vec3 in_col;
layout (location = 2) in vec2 in_tex_coord;

out vec2 fragTexCoord;
out vec3 fragCol;

uniform mat4 in_matrix;

void main() {
    gl_Position=in_matrix*vec4(in_pos.xyz,1.0);
    fragTexCoord=in_tex_coord;
    fragCol=in_col;
}

