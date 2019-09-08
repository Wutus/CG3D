#include "glwPointLightBulb.h"

glwPointLightBulb::glwPointLightBulb(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular, vec3 position, std::shared_ptr<glwModel> model3d, 
	vec3 distanceFactor, const std::string& name, mat4x4 internal) 
	: glwPointLight(color, ambient, diffuse, specular, position, name, distanceFactor), glwModelObject3D(model3d, position, name, internal)
{
}


glwPointLightBulb::~glwPointLightBulb()
{
}
