#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec3 io_worldSpacePosition;
out vec3 io_worldSpaceNormal;

out vec4 io_fragmentColor;
out vec2 io_texCoord;

out mat4 io_lightData;
out float io_isDirectionalLight;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform mat4 u_lightData;
uniform mat4 u_tangentToWorld;
uniform float u_isDirectionalLight;

void main()
{
    io_worldSpacePosition = vec3(u_model * vec4(position, 1.0f));
    io_worldSpaceNormal = (u_tangentToWorld * vec4(normal, 0.0f)).xyz;

    io_fragmentColor = color;
    io_texCoord = texCoord;
    io_lightData = u_lightData;
    io_isDirectionalLight = u_isDirectionalLight;

    gl_Position = u_projection * u_view * u_model * vec4(position, 1.0f);
};