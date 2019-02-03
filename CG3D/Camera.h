#pragma once
#include "Object3D.h"

class Camera : public Object3D
{
public:
	Camera(vec3 pos);
	Camera(vec3 pos, vec3 target);
	Camera(vec3 pos, Object3D target);
	virtual ~Camera();
	void LookAt(Object3D target);
	void LookAt(vec3 target);
};

