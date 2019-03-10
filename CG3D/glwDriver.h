#pragma once
#include "glwObject3D.h"
#include "glwWindow.h"

class glwDriver
{
public:
	glwDriver(std::shared_ptr<glwWindow> window, std::shared_ptr<glwObject3D> object);
	virtual ~glwDriver();
	std::shared_ptr<glwObject3D> Object;
protected:
	std::weak_ptr<glwWindow> window;
	virtual void FrameUpdateCallback(glwWindow & window, const FrameUpdateInfo & info);
	virtual void CursorMoveCallback(glwWindow & window, const CursorPos & cursorMove);
	virtual void CursorPositionCallback(glwWindow & window, const CursorPos & cursorPos);
	virtual void ScrollCallback(glwWindow & window, const ScrollOffset & scrollOff);
private:
	std::function<void(glwWindow & w, const CursorPos&)> mouseMoveCb;
	std::function<void(glwWindow & w, const CursorPos&)> mousePosCb;
	std::function<void(glwWindow & w, const ScrollOffset&)> scrollCb;
	std::function<void(glwWindow & w, const FrameUpdateInfo&)> updateCb;
	void InitCallbacks();
	void DestroyCallbacks();
};

