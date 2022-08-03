#version 460 core

out vec4 color;

in vec3 io_cameraPosition;

in vec3 io_worldSpacePosition;
in vec3 io_worldSpaceNormal;

in vec4 io_fragmentColor;
in vec2 io_texCoord;

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

vec3 specularReflection(float intensity, float factor, vec3 lightColor, float hardness, vec3 viewDirection, vec3 reflectionDirection)
{
    float a = clamp(dot(viewDirection, reflectionDirection), 0.0, 1.0);
    float p = pow(a, hardness);
    return a * intensity * factor * lightColor;
}

void main()
{
    vec3 normal = normalize(io_worldSpaceNormal);
    vec3 viewDirection = normalize(io_cameraPosition - io_worldSpacePosition);
    vec3 lightColor = vec3(1.0f, 1.0, 1.0f);
    vec3 lightPositon = vec3(0.0f, -10.0f, 0.0f);
    vec3 lightDirection = normalize(lightPositon - io_worldSpacePosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);

    // ambient
    vec3 ambientLightColor = vec3(0.75f, 0.75f, 1.0f);
    float ambientIntensity = 0.5f;
    float ambientFactor = 1.0f;
    vec3 ambient = ambientReflection(ambientIntensity, ambientFactor, ambientLightColor);

    // diffuse
    float diffuseIntensity = 0.8f;
    float diffuseFactor = 1.0f;
    vec3 diffuse = diffuseReflection(diffuseIntensity, diffuseFactor, lightColor, lightDirection, normal);

    // specular
    float specularIntensity = 1.0f;
    float specularFactor = 1.0f;
    float hardness = 64.0f;
    vec3 specular = specularReflection(specularIntensity, specularFactor, lightColor, hardness, viewDirection, reflectionDirection);

    // color
    vec4 light = vec4(ambient + diffuse + specular, 1.0f);
    vec4 texColor = texture(u_texture, io_texCoord);

    color = light * (io_fragmentColor * texColor);
};