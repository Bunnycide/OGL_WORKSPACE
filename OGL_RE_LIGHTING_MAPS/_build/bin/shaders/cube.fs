#version 400 core

uniform vec3 viewPos;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

const vec3 unit3 = vec3(1.0);

struct Material{    
    sampler2D diffuse;
    sampler2D specular;
    sampler2D glow;
    float shininess;
};

struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

void main(){        
    // ambient
    // -------
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // diffuse
    // -------
    // light dir
    vec3 lightDir = normalize(FragPos - light.position);    

    /* angle between normal and lightDir
       calculate diffuse for each fragment
       
       edit: Negated light dir for 
             dot product to work */

    float diff = max(dot(Normal, -lightDir), 0);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

    // specular
    // -------
    /**   
          Define specular strength so 
          the effect isn't too dominmant.
    **/
    float specularStrength = 0.5f;

    /**
        Calculate the direction from where
        the viewer is looking at the object
    **/
    vec3 viewDir = -normalize(FragPos - viewPos);    

    /**
        Calculate the reflected ray direction
    **/
    vec3 reflectDir = reflect(lightDir, Normal);
    
    // Calculate spec var    
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess * 128.0f);

    // Calcualte specular component
    vec3 specular =  light.specular * (spec * vec3(texture(material.specular, TexCoords)));

    vec3 emittion = vec3(texture(material.glow, TexCoords));

    // result         add all components    object color
    // ------         ------------------    ------------
    FragColor = vec4((ambient + diffuse + specular + emittion), 1.0);
}
