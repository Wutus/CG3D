#include "glwDriver.h"

glwDriver::glwDriver(std::weak_ptr<glwWindow> window, std::shared_ptr<glwObject3D> object) : Object(object), window(window)
{
}

glwDriver::~glwDriver()
{
}
