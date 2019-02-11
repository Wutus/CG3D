#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct CursorPos {
	double x;
	double y;
};

enum KeyState {
	RELEASED = 0,
	PRESSED = 1,
	REPEAT = 2
};

typedef unsigned int uint;

class glwWindow;

typedef void(*glwWindow_cb)(const glwWindow & window);

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
	GLFWwindow *window;
private:
	glwWindow_cb input_cb;
};

