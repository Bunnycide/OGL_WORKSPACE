#version 400

layout (location = 0) in vec3 vert_position;
layout (location = 1) in vec2 texcoords;

out vec2 out_texcoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main(){
    gl_Position     =  proj * view * model * vec4(vert_position, 1.0);
    out_texcoord    = texcoords;    
}
