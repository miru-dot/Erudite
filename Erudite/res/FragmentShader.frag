#version 460 core

out vec4 color;

smooth in vec4 fragmentColor;
uniform vec4 u_color;

void main()
{
    color = fragmentColor;
};