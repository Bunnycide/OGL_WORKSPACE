#version 330 core

out vec4 frag_color;

uniform vec3 object_color;
uniform vec3 light_color;

uniform vec3 light_pos;
uniform vec3 view_pos;

in vec3 normal;
in vec3 frag_pos;

void main(){
    // ambient
    float ambientStrength = 0.4;
    vec3 ambient = ambientStrength * light_color;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light_pos - frag_pos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light_color;

    // specular
    float specular_strength = 0.3;
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-lightDir, norm);
    
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 128);
    vec3 specular = specular_strength + spec * light_color;

    vec3 result = (ambient + diffuse + specular) * object_color;
    frag_color = vec4(result, 1.0);
}
