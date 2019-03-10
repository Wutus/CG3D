#pragma once
#include "glwDriver.h"

class CarDriver : public glwDriver
{
public:
	CarDriver();
	~CarDriver();
protected:
	virtual void FrameUpdateCallback(glwWindow & window, const FrameUpdateInfo & info) override;
private:
	vec3 velocity;
	vec3 acceleration;
};

