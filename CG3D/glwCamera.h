#pragma once
#include "glwObject3D.h"
#include <memory>

class glwCamera : public glwObject3D
{
public:
	glwCamera(vec3 pos);
	glwCamera(vec3 pos, vec3 target);
	glwCamera(vec3 pos, std::shared_ptr<glwObject3D> target);
	virtual ~glwCamera();
	void LookAt(std::shared_ptr<glwObject3D> target);
	void LookAt(vec3 target);

	// Inherited via glwObject3D
	virtual vec3 & position() override;
	virtual mat4x4 & model() override;
private:
	vec3 _pos;
	mat4x4 _model;
};

