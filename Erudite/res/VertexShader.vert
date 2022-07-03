#version 460 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

smooth out vec4 fragmentColor;
uniform mat4 u_mvp;

void main()
{
    gl_Position = u_mvp * position;
    fragmentColor = color;
};