#version 400 core

in vec3 Normal;
out vec4 FragColor;

float LinearizeDepth(float depth)
{
    float near = 0.1;
    float far = 100.0;
    float z = depth * 2.0 - 1.0; // Back to NDC
    return (2.0 * near) / (far + near - z * (far - near));
}

void main(){    
    FragColor = vec4(vec3(LinearizeDepth(gl_FragCoord.z)), 1.0);
}
