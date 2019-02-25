#include "glwSpotLight.h"

glwSpotLight::glwSpotLight(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular, vec3 pos, const std::string & name, vec3 dir, float cutOff, float outerCutOff, vec3 distanceFactor) : glwLightSource(color, ambient, diffuse, specular), glwObject3D(pos, name)
{
	this->direction = dir;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
	this->distanceFactor = distanceFactor;
}

glwSpotLight::~glwSpotLight()
{
}

glwSpotLight *glwSpotLight::Clone(const std::string & name)
{
	glwSpotLight *res = new glwSpotLight(color, ambient, diffuse, specular, _pos, name, direction, cutOff, outerCutOff, distanceFactor);
	res->_model = _model;
	return res;
}

void glwSpotLight::PreDraw(glwAdvancedShader & shader, mat4x4 model = mat4x4(1.0f))
{
	shader.addSpotLight(*this, model);
}
