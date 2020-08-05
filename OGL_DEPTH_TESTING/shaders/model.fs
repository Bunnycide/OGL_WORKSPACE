#version 400 core

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_normal1;

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

struct DirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;

uniform vec3 viewPos;

float calculateDiffuse(vec3 lightDir, vec3 normal);
float calculateSpecular(vec3 lightDir, vec3 normal, float shininess);

vec3 calculateDirLight( DirLight light, 
                        vec3 diffuseSample,
                        vec3 specularSample,
                        vec3 normalSample);

void main(){
    vec3 diffuseSample  =   texture(texture_diffuse1, 
                            TexCoords).rgb;                            
    vec3 specularSample =   
                            texture(texture_specular2, 
                            TexCoords).rgb;

    vec3 normalSample   =   texture(texture_normal1,
                            TexCoords).rgb;

    FragColor = vec4(
        calculateDirLight(  dirLight, 
                            diffuseSample, 
                            specularSample,
                            normalSample),
        1.0f                            
    );
    
}

vec3 calculateDirLight( DirLight light, 
                        vec3 diffuseSample,
                        vec3 specularSample,
                        vec3 normalSample){
    
    vec3 ambient    = light.ambient
                    * diffuseSample;

    vec3 diffuse    = calculateDiffuse(light.direction, normalSample)
                    * diffuseSample
                    * light.diffuse;

    vec3 specular   = calculateSpecular(light.direction, normalSample , 1.45)
                    * specularSample
                    * light.specular;

    return (  ambient 
            + diffuse
            + specular);
}

float calculateDiffuse(vec3 lightDir, vec3 normal){
   return max(
       dot(
            normal,
           -normalize(lightDir)
        ),
        0.0f
    );
}

float calculateSpecular(vec3 lightDir,
                        vec3 normal,
                        float shininess){
    /**
        Calculate the direction from where
        the viewer is looking at the object
    **/
    vec3 viewDir = normalize(FragPos - viewPos);

    /**
        Calculate the reflected ray direction
    **/
    vec3 reflectDir = reflect(lightDir, Normal);

    return pow(max(dot(reflectDir, -viewDir), 0.0), shininess);
                    
}