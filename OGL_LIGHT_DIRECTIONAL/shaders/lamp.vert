#version 330

layout (location = 0) in vec3 vert_position;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main(){
    gl_Position =  proj * view * model * vec4(vert_position, 1.0);
}
