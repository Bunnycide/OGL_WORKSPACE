#version 400
out vec4 frag_color;

in vec2 out_texcoord;

uniform sampler2D texsampler;   

void main(){
    frag_color = texture(texsampler, out_texcoord);
}
