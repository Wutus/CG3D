#pragma once
#include "glwPreDrawable.h"
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

class glwLightSource : public glwPreDrawable
{
public:
	glwLightSource(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular);
	~glwLightSource();
	vec3 color;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	// Inherited via glwPreDrawable
	virtual void PreDraw(glwAdvancedShader & shader, mat4x4 model = mat4x4(1.0f)) = 0;
};

