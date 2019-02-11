#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glwAdvancedShader.h"
#include "glwWindow.h"
#include "glwCamera.h"
#include "glwProjection.h"
#include "glwModelObject3D.h"

#include <iostream>

using namespace std;

void processInput(glwWindow & window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	glwWindow window(SCR_WIDTH, SCR_HEIGHT, "CG3D");
	glwAdvancedShader shader("cg.vs", "cg.fs");

	glwPointLight pLight(vec3(1.0f,1.0f,1.0f), vec3(0.5f,0.5f,0.5f), vec3(0.2f,0.2f,0.2f), vec3(0.4f,0.4f,0.4f), vec3(1.0f,1.0f,0.0f));
	glwDirectionalLight dLight(vec3(1.0f, 1.0f, 1.0f), vec3(0.5f, 0.5f, 0.5f), vec3(0.2f, 0.2f, 0.2f), vec3(0.4f, 0.4f, 0.4f), vec3(1.0f, 1.0f, 0.0f));

	glwProjection projection(SCR_WIDTH, SCR_HEIGHT);
	glwCamera camera(vec3(-2.0f,-2.0f,-2.0f));
	std::shared_ptr<glwModel> suit_model(new glwModel("resources/nanosuit/nanosuit.obj"));
	shared_ptr<glwDrawableObject3D> suit(new glwModelObject3D(suit_model, vec3(0.0f)));
	camera.LookAt(suit);
	shader.use();
	shader.addPointLight(pLight);

	while (!window.ShouldClose())
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.setCamera(camera);
		shader.setProjection(projection);
		suit->Draw(shader);
		window.SwapBuffers();
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(glwWindow & window)
{
	if (window.GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
		window.SetShouldClose(true);
}
