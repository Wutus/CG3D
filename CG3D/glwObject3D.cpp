#include "glwObject3D.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

glwObject3D::glwObject3D(vec3 pos)
{
	_pos = pos;
	_model = translate(mat4x4(1.0f), pos);
}

glwObject3D::~glwObject3D()
{
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
