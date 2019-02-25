#include "glwDirectionalLight.h"



glwDirectionalLight::glwDirectionalLight(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular, vec3 dir) : glwLightSource(color, ambient, diffuse, specular)
{
	this->direction = dir;
}


glwDirectionalLight::~glwDirectionalLight()
{
}

void glwDirectionalLight::PreDraw(glwAdvancedShader & shader, mat4x4 model)
{
	shader.addDirectionalLight(*this);
}
