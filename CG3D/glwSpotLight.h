#pragma once
#include "glwLightSource.h"
#include "glwObject3D.h"

class glwSpotLight : public glwLightSource, public glwObject3D
{
public:
	glwSpotLight(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular, vec3 pos, const string & name = "", vec3 dir = vec3(0.0f,-1.0f,0.0f), float cutOff = 12.5f, float outerCutOff = 15.0f, vec3 distanceFactor = vec3(1.0f,0.0f,0.0f));
	~glwSpotLight();
	virtual glwSpotLight *Clone(const std::string & name = "") override;
	vec3 distanceFactor;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	// Inherited via glwLightSource
	virtual void PreDraw(glwAdvancedShader & shader, mat4x4 model = mat4x4(1.0f)) override;
};

