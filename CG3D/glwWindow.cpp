#include "pch.h"
#include "glwWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

struct global_data
{
	glwWindow *act_win;
};

static global_data g_data;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	glwWindow & win = *(g_data.act_win);
	
	CursorPos pos;
	pos.x = xpos;
	pos.y = ypos;
	win.mousePosEvent.Invoke(pos);

	if (win.lastCursorPos.x == -1)
	{
		win.lastCursorPos = pos;
		return;
	}
	CursorPos move;
	move.x = pos.x - win.lastCursorPos.x;
	move.y = pos.y - win.lastCursorPos.y;
	win.lastCursorPos = pos;
	win.mouseMoveEvent.Invoke(move);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	glwWindow & win = *(g_data.act_win);

	ScrollOffset offset;
	offset.x = xoffset;
	offset.y = yoffset;
	win.scrollEvent.Invoke(offset);
}

glwWindow::glwWindow(uint width, uint height, std::string title) : scrollEvent(*this), mousePosEvent(*this), mouseMoveEvent(*this), frameUpdateEvent(*this)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	g_data.act_win = this;
	lastCursorPos.x = -1;
	lastCursorPos.y = -1;
	lastTime = glfwGetTime();
	frame = 0;
}


glwWindow::~glwWindow()
{
	g_data.act_win = nullptr;
}

bool glwWindow::ShouldClose() const
{
	return glfwWindowShouldClose(window);
}

void glwWindow::SetShouldClose(bool should)
{
	glfwSetWindowShouldClose(window, (int)should);
}

KeyState glwWindow::GetKey(int key) const
{
	return (KeyState)glfwGetKey(window, key);
}

CursorPos glwWindow::GetCursorPos() const
{
	CursorPos position;
	glfwGetCursorPos(window, &position.x, &position.y);
	return position;
}

void glwWindow::SetCursorsPos(CursorPos position)
{
	glfwSetCursorPos(window, position.x, position.y);
}

void glwWindow::SwapBuffers()
{
	glfwSwapBuffers(window);
}

void glwWindow::Update()
{
	float now = glfwGetTime();
	FrameUpdateInfo info;
	info.DeltaTime = now - lastTime;
	info.FrameNo = frame++;

	frameUpdateEvent.Invoke(info);

	lastTime = now;
}
