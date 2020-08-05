#version 330 core

out vec4 frag_color;

struct Light{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material{    
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform sampler2D emission;

in vec3 normal;
in vec3 frag_pos;
in vec2 out_texcoord;

uniform Material material;
uniform Light light;
uniform vec3 view_pos;


void main(){
    
    // ambient    
    vec3 ambient = light.ambient * mix(vec3(texture(material.diffuse, out_texcoord)) , vec3(texture(emission, out_texcoord)),1.0);
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - frag_pos);
    float diff = max(dot(norm, lightDir), 0.0);
    float c = texture(emission, out_texcoord).g;
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, out_texcoord));
    
    if(c > 0.5){
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, out_texcoord)) + vec3(texture(emission, out_texcoord));
    }    

    // specular    
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-lightDir, norm);
    
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess * 128);
    vec3 specular = light.specular * vec3(texture(material.specular, out_texcoord)) * spec;

    vec3 result = (ambient + diffuse + specular);
    frag_color = vec4(result, 1.0);
}