#version 400 core

layout (location = 0) in vec3 aVertex;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 texCoords;
out vec3 Normal;
out vec3 FragPos;

struct Camera{
    
    mat4 model;
    mat4 view;
    mat4 projection;
};

uniform Camera camera;

void main(){
    gl_Position = camera.projection * camera.view * camera.model * vec4(aVertex, 1.0);
    texCoords = aTexCoords;
    Normal = aNormal;
    FragPos = vec3(camera.model * vec4(aVertex, 1.0));
}
