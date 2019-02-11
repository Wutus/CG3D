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

	vec3 fogFactor;
private:
	vec3 _pos;
	mat4x4 _model;
};

