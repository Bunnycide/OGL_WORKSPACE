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
    float shininess;
};

struct DirLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight{
    vec3 position;
    vec3 direction;
    float cutoff;

    float constant;
    float linear;
    float quadratic;

    float outerCutoff;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

float calculateDiffuse(vec3 lightDir, vec3 normal){
    return max(dot(normalize(normal), -normalize(lightDir)), 0.0f);
}

float calculateSpecular(vec3 fragPos, vec3 viewPos, vec3 lightDir, float shininess){
    /**
        Calculate the direction from where
        the viewer is looking at the object
    **/
    vec3 viewDir = normalize(fragPos - viewPos);

    /**
        Calculate the reflected ray direction
    **/
    vec3 reflectDir = reflect(lightDir, Normal);

    return pow(max(dot(reflectDir, -viewDir), 0.0), shininess * 128.0f);
}

vec3 calculateSpotLight(SpotLight spotLight, 
                        vec3 normal, 
                        vec3 fragPos, 
                        vec3 viewPos){

    vec3 lightDir   = normalize(FragPos - spotLight.position); 
    float theta     = dot(normalize(spotLight.direction), normalize(lightDir));

    vec3 diffuseColor   = texture(material.diffuse,     TexCoords).rgb;
    vec3 specularColor  = texture(material.specular,    TexCoords).rgb;

    float distance = length(FragPos - spotLight.position);

    float attenuation = 1.0f /  (spotLight.constant + 
                                (spotLight.linear * distance) +
                                (spotLight.quadratic * pow(distance, 2)));

    float epsilon   = spotLight.cutoff - spotLight.outerCutoff;
    float intensity = clamp((theta - spotLight.outerCutoff)/epsilon, 0.0, 1.0);

    // ambient
    vec3 ambient    = spotLight.ambient * diffuseColor * attenuation;

         
    // diffuse
    vec3 diffuse    =   calculateDiffuse(lightDir, normal) * 
                        diffuseColor * 
                        spotLight.diffuse *
                        attenuation *                            
                        intensity;
    // // specular      
    vec3 specular   =   calculateSpecular(fragPos, spotLight.position, spotLight.direction, material.shininess) *
                        specularColor *
                        spotLight.specular *                              
                        attenuation *
                        intensity;

    return (ambient + diffuse + specular);    
}

vec3 calculatePointLight(   PointLight pointLight,                             
                            vec3 normal, 
                            vec3 fragPos, 
                            vec3 viewPos){
        
    // distance from light source 
    float distance = length(FragPos - pointLight.position);
    // attenuation for the given distance
    float attenuation = 1.0f /  (pointLight.constant + 
                                (distance * pointLight.linear) + 
                                (pow(distance, 2) * pointLight.quadratic));

    vec3 lightDir       = normalize(FragPos - pointLight.position);

    vec3 diffuseColor   = texture(material.diffuse,  TexCoords).rgb;
    vec3 specVal        = texture(material.specular, TexCoords).rgb;

    // ambient    
    vec3 ambient =  attenuation * 
                    pointLight.ambient * 
                    diffuseColor;

    // diffuse
    vec3 diffuse =  attenuation *                                 
                    calculateDiffuse(lightDir, normal) *
                    pointLight.diffuse *
                    diffuseColor;

    // specular
    vec3 specular = attenuation *
                    calculateSpecular(fragPos, viewPos, lightDir, material.shininess) *
                    pointLight.specular *
                    specVal;


    return (ambient + diffuse + specular);
}   

vec3 calculateDirLight(DirLight light,
                        vec3 normal,
                        vec3 fragPos,
                        vec3 viewPos){
    // ambient
    // -------
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // diffuse
    // -------
    // light dir    

    /* angle between normal and lightDir
       calculate diffuse for each fragment
       
       edit: Negated light dir for
             dot product to work */

    vec3 lightDir = normalize(light.direction);

    float diff = calculateDiffuse(lightDir, normalize(Normal));
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

    /**
        Calculate the direction from where
        the viewer is looking at the object
    **/
    vec3 viewDir = normalize(fragPos - viewPos);

    /**
        Calculate the reflected ray direction
    **/
    vec3 reflectDir = reflect(lightDir, normal);
    
    // Calculate spec var    
    float spec = calculateSpecular(fragPos, viewPos, light.direction, material.shininess);

    // Calcualte specular component
    vec3 specular =  light.specular * (spec * vec3(texture(material.specular, TexCoords)));
    
    // result         add all components    object color
    // ------         ------------------    ------------
    return (ambient + diffuse + specular);
}

void main(){
    vec3 dirLightColor = calculateDirLight( dirLight, 
                                            Normal, 
                                            FragPos, 
                                            viewPos);

    vec3 spotLightColor = calculateSpotLight(   spotLight,
                                                Normal,
                                                FragPos,
                                                viewPos);

    vec3 pointLightColor = calculatePointLight(pointLight,
                                                Normal,
                                                FragPos,
                                                viewPos
    );

    FragColor = vec4(spotLightColor + pointLightColor + dirLightColor, 1.0f);
}    