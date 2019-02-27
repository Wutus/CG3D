#pragma once
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

class glwAdvancedShader;

class glwPreDrawable
{
public:
	virtual void PreDraw(glwAdvancedShader & shader, mat4x4 model = mat4x4(1.0f)) = 0;
};

