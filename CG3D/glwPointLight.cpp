#include "glwPointLight.h"

glwPointLight::glwPointLight(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular, vec3 pos, vec3 distanceFactor) : glwLightSource(color, ambient, diffuse, specular), glwObject3D(pos)
{
	this->distanceFactor = distanceFactor;
}


glwPointLight::~glwPointLight()
{
}