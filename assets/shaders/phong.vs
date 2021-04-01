#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 RTR_MODEL;
uniform mat4 RTR_VIEW;
uniform mat4 RTR_PROJ;

void main()
{
    TexCoords = aTexCoords; 
    FragPos = vec3(RTR_MODEL* vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(RTR_MODEL))) * aNormal;
    gl_Position = RTR_PROJ * RTR_VIEW * RTR_MODEL * vec4(aPos, 1.0);
}