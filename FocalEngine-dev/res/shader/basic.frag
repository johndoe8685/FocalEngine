#version 330 core
in vec2 TextureCoordinates;
in vec3 Normal;
in vec3 FragmentPosition;

out vec4 FragColor;

const int MAX_POINT_LIGHTS = 32;

struct AmbientLight
{
    vec3 color;
    float intensity;
};

struct DirectionalLight
{
    vec3 color;
    vec3 position;
    vec3 direction;
    float intensity;
};

struct PointLight
{
    bool inUse;
    vec3 color;
    vec3 position;
    float intensity;
/*
    float constant;
    float linear;
    float exponent;
    */
};

uniform int pointLightCount;

uniform sampler2D aTexture;
uniform vec3 cameraPosition;

//Lights
uniform AmbientLight ambientLight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

vec4 CalculateLightByDirection(vec3 color, vec3 direction, float intensity)
{
    vec3 lightDirection = normalize(direction);
    float diffuseDifference =  max(dot(normalize(Normal), lightDirection), 0.0f);
    vec4 diffuseColor = vec4(color, 1.0f)   * intensity * diffuseDifference;
    
    vec4 specularColor = vec4(0, 0, 0, 0);

    if(diffuseDifference > 0.0f)
    {
        vec3 cameraDirection = normalize(cameraPosition - FragmentPosition);
        vec3 reflectedLightDirection = normalize(reflect(lightDirection, normalize(Normal)));
        float specularDifference = pow(max(dot(cameraDirection, reflectedLightDirection), 0.0), 32);
        if(specularDifference > 0.0f)
        {
            specularDifference = pow(specularDifference, 0.1f); //Materials are going to be added into specularDifference
            specularColor = vec4(color * specularDifference, 1.0f);
        }
    }
    
     return (diffuseColor + specularColor);
}

vec4 CalculateAmbientLight(AmbientLight ambientLight)
{
    return  vec4(ambientLight.color * ambientLight.intensity, 1.0f) ;
}

vec4 CalculateDirectionalLight(DirectionalLight directionalLight)
{
    return CalculateLightByDirection(directionalLight.color, directionalLight.direction, directionalLight.intensity);
}

vec4 CalculatePointLights()
{
    vec4 totalColor = vec4(0.0f);

    for(int i=0; i < pointLightCount; i++)
    {
        if(pointLights[i].inUse)
        {
            vec3 lightDirection = FragmentPosition - pointLights[i].position;
            float distance = length(lightDirection);

            vec4 color = CalculateLightByDirection(pointLights[i].color, lightDirection, pointLights[i].intensity);
            float atteunation = 0.1f * distance * distance + 0.2f * distance + 0.3f;

            totalColor += (color / atteunation);
        }
    }

    return totalColor;
}

void main()
{
    vec4 finalColor = vec4(0.0f);
    finalColor += CalculateAmbientLight(ambientLight);
    finalColor += CalculateDirectionalLight(directionalLight);
    finalColor += CalculatePointLights();
    FragColor = finalColor * texture(aTexture, TextureCoordinates);
}