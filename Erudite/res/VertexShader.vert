#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

out vec4 io_fragmentColor;
out vec2 io_texCoord;

uniform mat4 u_mvp;

uniform float u_time;
uniform float u_frequence;
uniform float u_amplitude;

void main()
{
    gl_Position = u_mvp * vec4(position, 1.0f);

    io_fragmentColor = color;
    io_texCoord = texCoord + (u_amplitude * sin(u_frequence * u_time));
};