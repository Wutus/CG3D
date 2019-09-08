#include "glwCarDriver.h"

#include <iostream>
using std::cout;
using std::endl;
const vec3 glwCarDriver::rotation_axis = vec3(0.0, 1.0, 0.0);
const vec3 glwCarDriver::move_direction = vec3(1.0, 0.0, 0.0);
const float glwCarDriver::rotation_speed = 30.0f;
const float glwCarDriver::accel_max = 2.0;
const float glwCarDriver::velocity_max = 8.0;
const float glwCarDriver::velocity_margin = 0.1;
const float glwCarDriver::velocity_zero_step = 0.7;
const float glwCarDriver::accel_decrese = 6.0;
const float glwCarDriver::accel_step = 7.0;

static float toZero(float value, float step)
{
	if (abs(value) < step)
		return 0.0f;
	value += -sign(value)*step;
	return value;
}

static float scale(float value, float min, float max)
{
	float v = value * sign(value);
	if (v > max)
		v = max;
	if (v < min)
		v = min;
	v = ((v - min) / (max - min))*max;
	return v * sign(value);
}

glwCarDriver::glwCarDriver(std::shared_ptr<glwWindow> window, std::shared_ptr<glwObject3D> object) : glwDriver(window, object)
{
}

glwCarDriver::~glwCarDriver()
{
}

void glwCarDriver::FrameUpdateCallback(glwWindow & window, const FrameUpdateInfo & info)
{
	velocity = toZero(velocity, velocity_zero_step*info.DeltaTime);
	acceleration = toZero(acceleration, accel_decrese*info.DeltaTime);
	if (window.GetKey(GLFW_KEY_W) == PRESSED)
	{
		acceleration = min(accel_max, acceleration + accel_step*info.DeltaTime);
	}

	if (window.GetKey(GLFW_KEY_S) == PRESSED)
	{
		acceleration = max(-accel_max, acceleration - accel_step*info.DeltaTime);
	}

	if (window.GetKey(GLFW_KEY_SPACE) == PRESSED)
	{
		acceleration = -sign(velocity) * 2 * accel_max;
	}
	
	velocity += acceleration * info.DeltaTime;
	velocity = scale(velocity, 0.0f, velocity_max);
	float act_velocity = scale(velocity, velocity_margin, velocity_max);

	if (act_velocity != 0)
	{
		float angle = rotation_speed * info.DeltaTime;

		if (window.GetKey(GLFW_KEY_A) == PRESSED)
		{
			Object->Rotate(angle, rotation_axis);
		}

		if (window.GetKey(GLFW_KEY_D) == PRESSED)
		{
			Object->Rotate(-angle, rotation_axis);
		}
	}

	vec3 translation = act_velocity * move_direction * info.DeltaTime;
	Object->Translate(translation);
}
