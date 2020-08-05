#version 400 core

uniform sampler2D WoodTexture;
uniform vec3 viewPos;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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
    vec3 ambient = light.ambient * material.ambient;

    // diffuse
    // -------
    // light dir
    vec3 lightDir = normalize(FragPos - light.position);    

    /* angle between normal and lightDir
       calculate diffuse for each fragment
       
       edit: Negated light dir for 
             dot product to work */

    float diff = max(dot(Normal, -lightDir), 0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

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
    vec3 specular =  light.specular * (spec * material.specular);

    // result         add all components    object color
    // ------         ------------------    ------------
    FragColor = vec4((ambient + diffuse + specular), 1.0);
}
