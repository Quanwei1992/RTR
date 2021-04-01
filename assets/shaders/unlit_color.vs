#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 RTR_MODEL;
uniform mat4 RTR_VIEW;
uniform mat4 RTR_PROJ;

void main()
{
    gl_Position = RTR_PROJ * RTR_VIEW * RTR_MODEL * vec4(aPos, 1.0);
}