#version 460 core

out vec4 color;

in vec4 io_fragmentColor;
in vec2 io_texCoord;
in vec3 io_normal;

uniform sampler2D u_texture;

void main()
{
    vec4 texColor = texture(u_texture, io_texCoord);
    color = io_fragmentColor * texColor;
};

/*
uniform float u_brightness;
uniform float u_contrast;
uniform float u_grayscale;

void setBrightness(inout vec3 c) 
{
    c = clamp(c + u_brightness, 0.0f, 1.0f);
}

void setContrast(inout vec3 c)
{
    float f = (u_contrast + 1.0f) / (1.01f - u_contrast);
    c = f * (c - 0.5f) + 0.5f;
}

void setGrayscale(inout vec3 c)
{
    float f = (c.r + c.g + c.b) / 3;
    c = mix(c, vec3(f), u_grayscale);
}*/