#version 460 core

out vec4 color;

in vec3 io_worldSpacePosition;
in vec3 io_worldSpaceNormal;

in vec4 io_fragmentColor;
in vec2 io_texCoord;

in mat4 io_lightData;

uniform sampler2D u_texture;

vec3 ambientReflection(float intensity, float factor, vec3 lightColor)
{
    return intensity * factor * lightColor;
}

vec3 diffuseReflection(float intensity, float factor, vec3 lightColor, vec3 lightDirection, vec3 normal) 
{
    float p = clamp(dot(lightDirection, normal), 0.0f, 1.0f);
    return p * intensity * factor * lightColor;
}

vec3 specularReflection(float intensity, float factor, vec3 lightColor, float hardness, vec3 viewDirection, vec3 reflectionDirection)
{
    float a = clamp(dot(viewDirection, reflectionDirection), 0.0f, 1.0f);
    float p = pow(a, hardness);
    return a * intensity * factor * lightColor;
}

void main()
{
    float ambientFactor = 1.0f;
    float diffuseFactor = 1.0f;
    float specularFactor = 1.0f;

    float ambientIntensity = io_lightData[0].w;
    float diffuseIntensity = io_lightData[1].w;
    float specularIntensity = io_lightData[2].w;
    float hardness = io_lightData[3].w;

    vec3 lightPositon = io_lightData[0].xyz;
    vec3 ambientLightColor = io_lightData[1].xyz;
    vec3 lightColor = io_lightData[2].xyz;
    vec3 viewPosition = io_lightData[3].xyz;
    
    vec3 normal = normalize(io_worldSpaceNormal);
    vec3 viewDirection = normalize(viewPosition - io_worldSpacePosition);
    vec3 lightDirection = normalize(lightPositon - io_worldSpacePosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);

    vec3 ambient = ambientReflection(ambientIntensity, ambientFactor, ambientLightColor);
    vec3 diffuse = diffuseReflection(diffuseIntensity, diffuseFactor, lightColor, lightDirection, normal);
    vec3 specular = specularReflection(specularIntensity, specularFactor, lightColor, hardness, viewDirection, reflectionDirection);

    // color
    vec3 texColor = texture(u_texture, io_texCoord).rgb;
    vec3 finalColor = (ambient + diffuse + specular) * texColor * io_fragmentColor.rgb;

    color = vec4(finalColor, 1.0f);
};