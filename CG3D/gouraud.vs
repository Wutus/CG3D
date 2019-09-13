#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

#define MAX_LIGHTS_SIZE 32

out vec2 TexCoords;
out vec3 FragPos;
out vec3 LightAmbient;
out vec3 LightDiffuse;
out vec3 LightSpecular;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shiness;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    vec3 distanceFactor;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    vec3 distanceFactor;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

uniform Material material;
uniform vec3 viewPos;
uniform DirLight dirLights[MAX_LIGHTS_SIZE];
uniform PointLight pointLights[MAX_LIGHTS_SIZE];
uniform SpotLight spotLights[MAX_LIGHTS_SIZE];
uniform int dirLightSize;
uniform int pointLightSize;
uniform int spotLightSize;

// function prototypes
void ConsiderDirLight(DirLight light, vec3 normal, vec3 viewDir);
void ConsiderPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
void ConsiderSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 DistVec(float distance);

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
	TexCoords = aTexCoords;
    vec3 Normal = mat3(transpose(inverse(model))) * aNormal;
    
    gl_Position = projection * view * vec4(FragPos, 1.0);

	vec3 norm = normalize(Normal);

	LightAmbient = LightDiffuse = LightSpecular = vec3(0.0, 0.0, 0.0);

    vec3 viewDir = normalize(viewPos - FragPos);
    
	// phase 1: directional lighting
    for(int i = 0; i < dirLightSize; ++i)
    {
        ConsiderDirLight(dirLights[i], norm, viewDir);
    }
    // phase 2: point lights
    for(int i = 0; i < pointLightSize; i++)
    {
        ConsiderPointLight(pointLights[i], norm, FragPos, viewDir);    
    }
    // phase 3: spot light
    for(int i = 0; i < spotLightSize; i++)
    {
        ConsiderSpotLight(spotLights[i], norm, FragPos, viewDir);
    }
}

// calculates the color when using a directional light.
void ConsiderDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shiness);
    // combine results
    LightAmbient += light.ambient;
    LightDiffuse += light.diffuse * diff;
    LightSpecular += light.specular * spec * vec3(texture(material.specular, TexCoords));
}

// calculates the color when using a point light.
void ConsiderPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shiness);
    // attenuation
    float distance = length(light.position - fragPos);
    vec3 distanceVec = DistVec(distance);
    float attenuation = 1.0 / dot(distanceVec, light.distanceFactor);    
    // combine results
    LightAmbient += light.ambient * attenuation;
    LightDiffuse += light.diffuse * diff * attenuation;
    LightSpecular += light.specular * spec * attenuation;
}

// calculates the color when using a spot light.
void ConsiderSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shiness);
    // attenuation
    float distance = length(light.position - fragPos);
    vec3 distanceVec = DistVec(distance);
    float attenuation = 1.0 / dot(distanceVec, light.distanceFactor);
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    LightAmbient += light.ambient * attenuation * intensity;
    LightDiffuse += light.diffuse * diff * attenuation * intensity;
    LightSpecular += light.specular * spec * attenuation * intensity;
}

vec3 DistVec(float distance)
{
    return vec3(1.0, distance, distance * distance);
}