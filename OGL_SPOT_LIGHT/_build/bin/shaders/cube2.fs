#version 400 core

struct Light{    
    vec3 lightPos;
};

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;   
};

uniform Material material;
uniform Light light;
uniform vec3 viewDir;
uniform vec3 lightColor;
uniform vec3 viewPos;

uniform bool specularOn;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
out vec4 FragColor;

void main(){        

    vec3 norm = normalize(Normal);

    // ambient (ambientStrength = 0.1)
    vec3 ambient = 0.1 * lightColor;   

    // diffuse
    vec3 lightDir = normalize(light.lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    vec3 reflectDir = normalize(reflect(-lightDir, norm));
    vec3 viewDir = normalize(viewPos - FragPos);
    float spec = pow(max(dot(reflectDir, reflectDir),0.0) ,material.shininess);
    vec3 specular = 0.7 * spec * texture(material.specular, TexCoords).rgb;

    vec3 result = (ambient + diffuse + specular) * texture(material.diffuse, TexCoords).rgb;   
    if(! specularOn){        
        result = (ambient + diffuse) * texture(material.diffuse, TexCoords).rgb;
    }
    
    FragColor = vec4(result, 1.0);
}
