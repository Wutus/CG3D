#pragma once
#include <string>
#include <GLFW/glfw3.h>
typedef unsigned int uint;

class glwWindow;

typedef void(*glwWindow_cb)(const glwWindow & window);

class glwWindow
{
public:
	glwWindow(uint width, uint height, std::string title);
	~glwWindow();
	void RegisterCallback(glwWindow_cb callback);
private:
	GLFWwindow *window;
	glwWindow_cb input_cb;
};

