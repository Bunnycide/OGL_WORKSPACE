#version 330 core

layout (location = 0) in vec3 vert_position;
layout (location = 1) in vec3 vert_normal;
layout (location = 2) in vec2 tex_coords;

out vec2 out_texcoord;
out vec3 normal;
out vec3 frag_pos;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main(){
    gl_Position     =  proj * view * model * vec4(vert_position, 1.0);    
    frag_pos = vec3(model * vec4(vert_position, 1.0));
    normal = vert_normal;
    out_texcoord = tex_coords;
}
