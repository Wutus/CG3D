#pragma once
#include "glm/gtc/type_ptr.hpp"
#include "glwPreDrawable.h"

using namespace glm;

class glwProjection : glwPreDrawable
{
public:
	glwProjection(int screenWidth, int screenHeight, float FOV = 45, float nearDist = 0.1f, float farDist = 100.0f);
	~glwProjection();
	const mat4x4 & projection() const;
	virtual void PreDraw(glwAdvancedShader & shader, mat4x4 model = mat4x4(1.0f)) override;
private:
	mat4x4 _projection;
};

