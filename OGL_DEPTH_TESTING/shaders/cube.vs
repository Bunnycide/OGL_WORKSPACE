#version 400 core

layout (location = 0) in vec3 aVert;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

struct Camera{
    mat4 model;
    mat4 view;
    mat4 projection;
};

uniform Camera camera;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

void main(){
    gl_Position = camera.projection * camera.view * camera.model * vec4(aVert, 1.0);
    TexCoords = aTexCoords;        
    Normal = normalize(aNormal);
    FragPos = (camera.model * vec4(aVert, 1.0)).rgb;
}