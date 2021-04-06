#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D sampler_diffuse;
uniform vec3 uKs;
uniform vec3 uLightPos;
uniform vec3 uCameraPos;
uniform float uLightIntensity;

void main()
{    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(uLightPos - FragPos);
    vec3 viewDir = normalize(uCameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float diff = max(dot(lightDir,norm),0.0);
    float light_atten_coff = uLightIntensity / length(uLightPos - FragPos);
    vec3 color = pow(texture2D(sampler_diffuse,TexCoords).rgb,vec3(2.2));
    vec3 ambient = color * 0.03;
    vec3 diffuse = color * diff * light_atten_coff;

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = uKs * spec * light_atten_coff;
    vec3 finalColor = ambient + diffuse + specular;
    finalColor = pow(finalColor,vec3(1.0f/2.2));
    FragColor = vec4(finalColor,1.0f);
}