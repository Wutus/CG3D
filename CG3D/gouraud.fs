#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shiness;
}; 

uniform Material material;

in vec3 LightAmbient;
in vec3 LightDiffuse;
in vec3 LightSpecular;

in vec3 FragPos;
in vec2 TexCoords;

void main()
{   
    vec3 ambient = LightAmbient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = LightDiffuse * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = LightSpecular * vec3(texture(material.specular, TexCoords));

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}