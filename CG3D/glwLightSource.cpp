#include "glwLightSource.h"

glwLightSource::glwLightSource(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular)
{
	this->color = color;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

glwLightSource::~glwLightSource()
{
}
