#version 400 core

in vec3 Normal;
out vec4 FragColor;

void main(){    
    FragColor = vec4(Normal, 1.0);
}
