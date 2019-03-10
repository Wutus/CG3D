#include "glwDriver.h"

glwDriver::glwDriver(std::shared_ptr<glwWindow> window, std::shared_ptr<glwObject3D> object)
{
	this->window = window;
	this->Object = object;
	InitCallbacks();
}

glwDriver::~glwDriver()
{
	DestroyCallbacks();
}

void glwDriver::FrameUpdateCallback(glwWindow & window, const FrameUpdateInfo & info)
{
}

void glwDriver::CursorMoveCallback(glwWindow & window, const CursorPos & cursorMove)
{
}

void glwDriver::CursorPositionCallback(glwWindow & window, const CursorPos & cursorPos)
{
}

void glwDriver::ScrollCallback(glwWindow & window, const ScrollOffset & scrollOff)
{
}

void glwDriver::InitCallbacks()
{
	mousePosCb = [this](glwWindow & w, const CursorPos & cp) {this->CursorPositionCallback(w,cp); };
	mouseMoveCb = [this](glwWindow & w, const CursorPos & cp) {this->CursorMoveCallback(w, cp); };
	scrollCb = [this](glwWindow & w, const ScrollOffset & so) {this->ScrollCallback(w, so); };
	updateCb = [this](glwWindow & w, const FrameUpdateInfo & info) {this->FrameUpdateCallback(w, info); };

	window.lock()->mousePosEvent += mousePosCb;
	window.lock()->mouseMoveEvent += mouseMoveCb;
	window.lock()->scrollEvent += scrollCb;
	window.lock()->frameUpdateEvent += updateCb;
}

void glwDriver::DestroyCallbacks()
{
	window.lock()->mousePosEvent -= mousePosCb;
	window.lock()->mouseMoveEvent -= mouseMoveCb;
	window.lock()->frameUpdateEvent -= updateCb;
	window.lock()->scrollEvent -= scrollCb;
}
