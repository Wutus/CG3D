#include "glwProjection.h"
#include "glwAdvancedShader.h"

glwProjection::glwProjection(int screenWidth, int screenHeight, float FOV, float nearDist, float farDist)
{
	_projection = perspective(radians(FOV), screenWidth / (float)screenHeight, nearDist, farDist);
}

glwProjection::~glwProjection()
{
}

const mat4x4 & glwProjection::projection() const
{
	return _projection;
}

void glwProjection::PreDraw(glwAdvancedShader & shader, mat4x4 model)
{
	shader.setProjection(*this);
}
