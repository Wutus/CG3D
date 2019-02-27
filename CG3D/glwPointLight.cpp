#include "glwPointLight.h"
#include "glwAdvancedShader.h"

glwPointLight::glwPointLight(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular, vec3 pos, const std::string & name, vec3 distanceFactor) : glwLightSource(color, ambient, diffuse, specular), glwObject3D(pos, name)
{
	this->distanceFactor = distanceFactor;
}


glwPointLight::~glwPointLight()
{
}

glwPointLight * glwPointLight::Clone(const std::string & name)
{
	glwPointLight *res = new glwPointLight(color, ambient, diffuse, specular, _pos, name, distanceFactor);
	res->_model = _model;
	return res;
}

void glwPointLight::PreDraw(glwAdvancedShader & shader, mat4x4 model)
{
	shader.addPointLight(*this, model);
}
