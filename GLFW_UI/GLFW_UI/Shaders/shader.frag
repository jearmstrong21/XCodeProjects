#version 330

in vec2 fragTexCoord;
in vec3 fragCol;

out vec4 FragColor;

uniform sampler2D inTexture1;

void main() {
    FragColor=vec4(texture(inTexture1,fragTexCoord).xyz,1.0)*vec4(fragCol.xyz,1.0);
}
