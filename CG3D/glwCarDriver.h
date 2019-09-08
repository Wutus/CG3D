#pragma once
#include "glwDriver.h"
class glwCarDriver : public glwDriver
{
public:
	glwCarDriver(std::shared_ptr<glwWindow> window, std::shared_ptr<glwObject3D> object);
	virtual ~glwCarDriver();
	float acceleration;
	float velocity;
	const static vec3 rotation_axis;
	const static vec3 move_direction;
	const static float rotation_speed;
	const static float accel_max;
	const static float velocity_max;
	const static float velocity_margin;
	const static float velocity_zero_step;
	const static float accel_decrese;
	const static float accel_step;
protected:
	virtual void FrameUpdateCallback(glwWindow & window, const FrameUpdateInfo & info);

};

