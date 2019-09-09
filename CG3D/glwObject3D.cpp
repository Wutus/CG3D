#include "glwObject3D.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

unsigned int glwObject3D::counter = 0;

glwObject3D::glwObject3D()
{
	this->name = getNewName();
}

glwObject3D::glwObject3D(vec3 pos, const std::string & name)
{
	_pos = pos;
	_model = translate(mat4x4(1.0f), pos);
	this->name = name == ""? getNewName() : name;
}

glwObject3D::~glwObject3D()
{
}

glwObject3D *glwObject3D::Clone(const std::string & name)
{
	glwObject3D *res = new glwObject3D(position(), name);
	res->_model = _model;
	return res;
}

const vec3 & glwObject3D::position() const
{
	return _pos;
}

const mat4x4 & glwObject3D::model() const
{
	return _model;
}

void glwObject3D::Rotate(float degrees, vec3 axis)
{
	_model = rotate(model(), radians(degrees), axis);
}

void glwObject3D::Translate(vec3 translation)
{
	_pos += translation;
	_model = translate(model(), translation);
}

void glwObject3D::Scale(vec3 coef)
{
	_model = scale(model(), coef);
}

void glwObject3D::Reset()
{
	_model = mat4x4(1.0f);
	_pos = vec3(0.0f);
}

std::string glwObject3D::getNewName()
{
	return "obj" + std::to_string(counter++);
}
