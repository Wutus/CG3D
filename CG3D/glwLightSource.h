#pragma once
#include "glwObject3D.h"
#include "glwPreDrawable.h"

using namespace std;

class glwLightSource : public glwPreDrawable
{
public:
	glwLightSource(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular);
	~glwLightSource();
	vec3 color;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

