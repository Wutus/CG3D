#pragma once
#include "glwObject3D.h"
#include "glwWindow.h"

class glwDriver
{
public:
	glwDriver(glwWindow & window, std::shared_ptr<glwObject3D> object);
	~glwDriver();
};

