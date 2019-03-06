#pragma once
#include "glwObject3D.h"
#include "glwWindow.h"

class glwDriver
{
public:
	glwDriver(std::weak_ptr<glwWindow> window, std::shared_ptr<glwObject3D> object);
	~glwDriver();
	std::shared_ptr<glwObject3D> Object;
protected:
	std::weak_ptr<glwWindow> window;
	virtual void FrameUpdate(glwWindow &) = 0;
};

