#include "glwProjection.h"

glwProjection::glwProjection(int screenWidth, int screenHeight, float FOV, float near, float far)
{
	_projection = glm::perspective(radians(FOV), screenWidth / (float)screenHeight, near, far);
}

glwProjection::~glwProjection()
{
}

const mat4x4 & glwProjection::projection() const
{
	return _projection;
}
