#pragma once
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

class glwProjection
{
public:
	glwProjection(int screenWidth, int screenHeight, float FOV = 45, float near = 0.1f, float far = 100.0f);
	~glwProjection();
	const mat4x4 & projection() const;
private:
	mat4x4 _projection;
};

