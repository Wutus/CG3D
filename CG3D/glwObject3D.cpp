#include "glwObject3D.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

glwObject3D::glwObject3D()
{
}

glwObject3D::~glwObject3D()
{
}

void glwObject3D::Rotate(float degrees, vec3 axis)
{
	model() = rotate(model(), radians(degrees), axis);
}

void glwObject3D::Translate(vec3 translation)
{
	position() += translation;
	model() = translate(model(), translation);
}

void glwObject3D::Scale(vec3 coef)
{
	model() = scale(model(), coef);
}
