#version 400 core

uniform sampler2D WoodTexture;
uniform vec3 viewPos;

const vec3 lightColor   = vec3(1.0f, 1.0f, 1.0f);
const vec3 objectColor  = vec3(1.0f, 0.5f, 0.31f);
const vec3 lightPos     = vec3(1.2f, 1.0f, 2.0f);

const float ambientStrength = 0.1f;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

void main(){        
    // ambient
    // -------
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    // -------
    // light dir
    vec3 lightDir = normalize(FragPos - lightPos);    

    /* angle between normal and lightDir
       calculate diffuse for each fragment
       
       edit: Negated light dir for 
             dot product to work */

    float diff = max(dot(Normal, -lightDir), 0);
    vec3 diffuse = lightColor * diff;

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
    float spec = pow(  max(dot(reflectDir, viewDir), 0.0), 32);

    // Calcualte specular component
    vec3 specular = specularStrength * spec * lightColor;

    // result         add all components    object color
    // ------         ------------------    ------------
    FragColor = vec4((ambient + diffuse + specular) * objectColor, 1.0);
}
