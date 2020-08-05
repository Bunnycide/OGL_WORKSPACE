#version 400 core

layout (location = 0) in vec3 aVertex;

struct Camera{
    
    mat4 model;
    mat4 view;
    mat4 projection;
};

uniform Camera camera;

void main(){
    gl_Position = camera.projection * camera.view * camera.model * vec4(aVertex, 1.0);
}
