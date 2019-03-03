#pragma once
#include "glwWindow.h"

class glwInputPrecessable
{
public:
	glwInputPrecessable();
	~glwInputPrecessable();
	virtual void ProcessInput(const glwWindow & window) = 0;
};

