#pragma once
#include "glwModelObject3D.h"
#include "glwPointLight.h"

class glwPointLightBulb : public glwPointLight, public glwModelObject3D
{
public:
	glwPointLightBulb(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular, vec3 position, std::shared_ptr<glwModel> model3d, 
		vec3 distanceFactor = vec3(1.0f, 0.0f, 0.0f), const std::string& name = "", mat4x4 internal = mat4x4(1.0f));
	~glwPointLightBulb();
};

