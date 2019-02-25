#pragma once
#include "glwObject3D.h"
#include "glwPreDrawable.h"
#include <memory>

class glwCamera : public glwObject3D, public glwPreDrawable
{
public:
	glwCamera(vec3 pos);
	glwCamera(vec3 pos, vec3 target);
	glwCamera(vec3 pos, std::shared_ptr<glwObject3D> target);
	virtual ~glwCamera();
	void LookAt(std::shared_ptr<glwObject3D> target);
	void LookAt(vec3 target);
	const static vec3 up;
	vec3 fogFactor;

	// Inherited via glwPreDrawable
	virtual void PreDraw(glwAdvancedShader & shader, mat4x4 model = mat4x4(1.0f)) override;
};

