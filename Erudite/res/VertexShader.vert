#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec3 io_cameraPosition;
out vec3 io_worldSpacePosition;
out vec3 io_worldSpaceNormal;

out vec4 io_fragmentColor;
out vec2 io_texCoord;
out vec3 io_normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_tangentToWorld;

uniform vec3 u_cameraPosition;

void main()
{
    vec4 worldSpacePosition = u_model * vec4(position, 1.0f);
    vec4 worldSpaceNormal = u_tangentToWorld * vec4(normal, 0.0f);

    io_worldSpacePosition = worldSpacePosition.xyz;
    io_worldSpaceNormal = worldSpaceNormal.xyz;

    io_fragmentColor = color;
    io_texCoord = texCoord;
    io_normal = normal;
    io_cameraPosition = u_cameraPosition;

    gl_Position = u_projection * u_view * worldSpacePosition;
};