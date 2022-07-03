#version 460 core

out vec4 color;

in vec4 io_fragmentColor;
in vec2 io_texCoord;

uniform sampler2D u_texture;

void main()
{
    vec4 texColor = texture(u_texture, io_texCoord);
    color = io_fragmentColor * texColor; 
};