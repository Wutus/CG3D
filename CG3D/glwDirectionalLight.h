#pragma once
#include "glwLightSource.h"

class glwDirectionalLight :
	public glwLightSource
{

public:
	glwDirectionalLight(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular, vec3 pos, vec3 dir = vec3(0.0f, -1.0f, 0.0f));
	~glwDirectionalLight();
	vec3 direction;
};

