#version 330 core

out vec4 frag_color;

struct Material{    
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;
};

uniform Material material;
uniform Light light;

// uniform vec3 light_pos;
uniform vec3 view_pos;

in vec3 normal;
in vec3 frag_pos;
in vec2 out_texcoord;

void main(){
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, out_texcoord));
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * ( diff *  vec3(texture(material.diffuse, out_texcoord)));

    // specular  
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-lightDir, norm);    
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, out_texcoord)));

    vec3 result = (ambient + diffuse + specular);
    frag_color = vec4(result, 1.0);
}
