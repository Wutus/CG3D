#include "Object3D.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

Object3D::Object3D()
{
}


Object3D::Object3D(vec4 position)
{
	this->position = position;
	this->internal = mat4(1.0f);
	this->model = mat4(1.0f);
}

Object3D::Object3D(vec4 position, mat4x4 internal)
{
	this->position = position;
	this->internal = internal;
	this->model = mat4(1.0f);
}

Object3D::~Object3D()
{
}

void Object3D::Rotate(float degrees, vec3 axis)
{
	model = rotate(model, radians(degrees), axis);
}

void Object3D::Translate(vec3 translation)
{
	model = translate(model, translation);
}

void Object3D::Scale(vec3 coef)
{
	model = scale(model, coef);
}
