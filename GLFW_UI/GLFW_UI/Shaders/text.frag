#version 330

in vec2 fragTexCoord;
in vec3 fragCol;

out vec4 FragColor;

uniform sampler2D inTexture;

void main() {
    FragColor=vec4(texture(inTexture,fragTexCoord).xyz,1.0)*vec4(fragCol.xyz,1.0);
}

