#pragma once
#include "glwObject3D.h"

using namespace std;

class glwLightSource
{
public:
	glwLightSource(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular);
	~glwLightSource();
	vec3 color;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

