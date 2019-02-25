#pragma once
#include "glwAdvancedShader.h"

class glwPreDrawable
{
public:
	glwPreDrawable() = delete;
	virtual void PreDraw(glwAdvancedShader & shader, mat4x4 model = mat4x4(1.0f)) = 0;
};

