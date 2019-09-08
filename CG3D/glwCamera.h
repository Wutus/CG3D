#pragma once
#include "glwObject3D.h"
#include "glwPreDrawable.h"
#include <memory>

class glwCamera : public glwObject3D, public glwPreDrawable
{
public:
	glwCamera(vec3 pos, const std::string & name = "");
	glwCamera(vec3 pos, vec3 target, const std::string & name = "");
	glwCamera(vec3 pos, std::shared_ptr<glwObject3D> target, const std::string & name = "");
	virtual ~glwCamera();
	void LookAt(std::shared_ptr<glwObject3D> target);
	void LookAt(vec3 target);
	const static vec3 up;
	vec3 fogFactor;
	vec3 target;
	// Inherited via glwPreDrawable
	virtual void PreDraw(glwAdvancedShader & shader, mat4x4 model = mat4x4(1.0f)) override;
};

