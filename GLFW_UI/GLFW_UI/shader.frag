#version 330

in vec2 fragTexCoord;

out vec4 FragColor;

void main() {
    
    FragColor = vec4(fragTexCoord, 0.0, 0.0);
}
