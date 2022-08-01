#version 460 core

out vec4 color;

in vec3 io_worldPosition;
in vec4 io_fragmentColor;
in vec2 io_texCoord;
in vec3 io_normal;

uniform sampler2D u_texture;

vec3 ambientReflection(float intensity, float factor, vec3 lightColor)
{
    return intensity * factor * lightColor;
}

vec3 diffuseReflection(float intensity, float factor, vec3 lightColor, vec3 lightDirection, vec3 normal) 
{
    float p = clamp(dot(lightDirection, normal), 0.0, 1.0);
    return p * intensity * factor * lightColor;
}

void main()
{
    vec3 ambientLightColor = vec3(0.75f, 0.75f, 1.0f);
    vec3 lightColor = vec3(1.0f, 0.75, 0.0f);

    vec3 lightPositon = vec3(0.0f, 2.0f, 0.0f);
    vec3 lightDirection = normalize(lightPositon - io_worldPosition);
    vec3 normal = normalize(io_normal);

    float ambientIntensity = 0.5f;
    float diffuseIntensity = 0.75f;

    float ambientFactor = 1.0f;
    float diffuseFactor = 1.0f;

    vec3 ambient = ambientReflection(ambientIntensity, ambientFactor, ambientLightColor);
    vec3 diffuse = diffuseReflection(diffuseIntensity, diffuseFactor, lightColor, lightDirection, normal);

    vec4 light = vec4(ambient + diffuse, 1.0f);
    vec4 texColor = texture(u_texture, io_texCoord);
    color = light * (io_fragmentColor * texColor);
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