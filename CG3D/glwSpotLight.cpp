#include "glwSpotLight.h"

glwSpotLight::glwSpotLight(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular, vec3 pos, vec3 dir, float cutOff, float outerCutOff, vec3 distanceFactor) : glwLightSource(color, ambient, diffuse, specular), glwObject3D(pos)
{
	this->direction = dir;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
	this->distanceFactor = distanceFactor;
}

glwSpotLight::~glwSpotLight()
{
}
