#pragma once
#include "glwLightSource.h"
#include "glwObject3D.h"

class glwPointLight :
	public glwLightSource, public glwObject3D
{
public:
	glwPointLight(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular, vec3 pos, const std::string & name = "", vec3 distanceFactor = vec3(1.0f,0.0f,0.0f));
	~glwPointLight();
	vec3 distanceFactor;
};

