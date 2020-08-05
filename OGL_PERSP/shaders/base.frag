#version 400
out vec4 frag_color;

in vec2 given_tex_coord;

uniform sampler2D ourTexture;

void main(){
    frag_color = texture(ourTexture, given_tex_coord) ;    
}
