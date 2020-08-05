#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoord;

out vec2 given_tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    given_tex_coord = texcoord;
    gl_Position = projection * view * model * vec4(position, 1.0) ;
}
