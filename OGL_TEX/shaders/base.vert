#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texcoord;

out vec3 given_frag_color;
out vec2 given_tex_coord;

void main(){
    given_frag_color = color;
    given_tex_coord = texcoord;
    gl_Position = vec4(position, 1.0);
}
