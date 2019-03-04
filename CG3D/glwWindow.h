#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Event.h"

struct CursorPos {
	double x;
	double y;
};

struct ScrollOffset {
	double x;
	double y;
};

enum KeyState {
	RELEASED = 0,
	PRESSED = 1,
	REPEAT = 2
};

struct FrameUpdateInfo
{
	unsigned long long FrameNo;
	float DeltaTime;
};

typedef unsigned int uint;

class glwWindow
{
public:
	glwWindow(uint width, uint height, std::string title);
	~glwWindow();
	bool ShouldClose() const;
	void SetShouldClose(bool should);
	KeyState GetKey(int key) const;
	CursorPos GetCursorPos() const;
	void SetCursorsPos(CursorPos position);
	void SwapBuffers();
	void Update();
	Event<glwWindow, CursorPos> mousePosEvent;
	Event<glwWindow, CursorPos> mouseMoveEvent;
	Event<glwWindow, ScrollOffset> scrollEvent;
	Event<glwWindow, FrameUpdateInfo> frameUpdateEvent;
	GLFWwindow *window;
private:
	unsigned long long frame;
	float lastTime;
	CursorPos lastCursorPos;
	friend static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	friend static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

