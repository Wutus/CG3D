#include "CarDriver.h"



CarDriver::CarDriver()
{
}


CarDriver::~CarDriver()
{
}

void CarDriver::FrameUpdateCallback(glwWindow & window, const FrameUpdateInfo & info)
{
	if (window.GetKey(GLFW_KEY_W) == KeyState.PRESSED)
		acceleration.x = 1;

	velocity +=
}
