#include "pch.h"
#include "glwWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

glwWindow::glwWindow(uint width, uint height, std::string title)
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
}


glwWindow::~glwWindow()
{
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
