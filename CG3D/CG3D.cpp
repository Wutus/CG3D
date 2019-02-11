#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glwAdvancedShader.h"
#include "glwWindow.h"
#include "glwMovingCamera.h"
#include "glwProjection.h"
#include "glwModelObject3D.h"

#include <iostream>

using namespace std;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

bool firstMouse = true;
glwMovingCamera camera(vec3(0.0f, 0.0f, 0.0f));


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
	glwWindow window(SCR_WIDTH, SCR_HEIGHT, "CG3D");
	glwAdvancedShader shader("cg.vs", "cg.fs");

	glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);

	glfwSetCursorPosCallback(window.window, mouse_callback);
	glfwSetScrollCallback(window.window, scroll_callback);

	glwDirectionalLight dLight(vec3(1.0f, 1.0f, 1.0f), vec3(0.5f, 0.5f, 0.5f), vec3(0.2f, 0.2f, 0.2f), vec3(0.4f, 0.4f, 0.4f));
	glwSpotLight sLight(vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.5f, 0.5f), vec3(0.2f, 0.2f, 0.2f), vec3(0.4f, 0.4f, 0.4f), vec3(-0.25f, 13.25f, 5.0f), vec3(0.0f, 0.0f, -1.0f));

	std::shared_ptr<glwModel> suit_model(new glwModel("resources/streetlamp/StreetLamp.obj"));
	shared_ptr<glwModelObject3D> suit(new glwModelObject3D(suit_model, vec3(0.0f)));
	//camera.LookAt(suit);
	shader.use();
	//shader.addDirectionalLight(dLight);
	//shader.addSpotLight(sLight);

	while (!window.ShouldClose())
	{
		cout << "Camera pos: " << camera.position().x << " " << camera.position().y << " " << camera.position().z << " front: " << camera.Front.x << " " << camera.Front.y << " " << camera.Front.z << endl;
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		shader.resetLights();
		glwPointLight pLight(vec3(1.0f, 1.0f, 1.0f), vec3(0.5f, 0.5f, 0.5f), vec3(0.2f, 0.2f, 0.2f), vec3(0.4f, 0.4f, 0.4f), camera.position(), vec3(1.0f, 1.0f, 1.0f));
		shader.addPointLight(pLight);

		processInput(window.window);
		glClearColor(0.2f, 0.3f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glwProjection projection(SCR_WIDTH, SCR_HEIGHT, camera.Zoom);
		shader.setCamera(camera);
		shader.setProjection(projection);
		suit->Draw(shader);
		window.SwapBuffers();
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}