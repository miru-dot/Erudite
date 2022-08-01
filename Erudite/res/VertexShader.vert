#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec3 io_worldPosition;
out vec4 io_fragmentColor;
out vec2 io_texCoord;
out vec3 io_normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    vec4 worldPos = u_view * u_model * vec4(position, 1.0f);
    gl_Position = u_projection * worldPos;

    io_worldPosition = worldPos.xyz;
    io_fragmentColor = color;
    io_texCoord = texCoord;
    io_normal = normal;
};