#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glwAdvancedShader.h"
#include "glwWindow.h"
#include "glwFreeCamera.h"
#include "glwProjection.h"
#include "glwModelObject3D.h"

#include <iostream>

using namespace std;

static void processInput(glwWindow & window, const FrameUpdateInfo& info);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	shared_ptr<glwWindow> window(new glwWindow(SCR_WIDTH, SCR_HEIGHT, "CG3D"));
	glwAdvancedShader shader("cg.vs", "cg.fs");
	glwFreeCamera camera(vec3(0.0f, 0.0f, 0.0f), window);

	glEnable(GL_DEPTH_TEST);

	//glwDirectionalLight dLight(vec3(0.0f, 1.0f, 0.0f), vec3(0.01f, 0.01f, 0.01f), vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, -0.2f, 1.0f));
	//glwDirectionalLight dLight(vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f));

	window->frameUpdateEvent += processInput;

	shared_ptr<glwModel> race_track_model(new glwModel("resources/track2/track01_.3ds"));
	shared_ptr<glwModelObject3D> race_track(new glwModelObject3D(race_track_model, vec3(0.0f), "race_track", rotate(scale(mat4x4(1.0f), vec3(0.01f)), radians(270.0f), vec3(1.0f, 0.0f, 0.0f))));

	shared_ptr<glwModel> car_model(new glwModel("resources/car_models/car_green.obj"));
	shared_ptr<glwModelObject3D> car(new glwModelObject3D(car_model, vec3(0.0f, 0.0f, 0.0f), "car"));
	//camera.LookAt(suit);
	shader.use();
	//shader.addSpotLight(sLight);

	while (!window->ShouldClose())
	{
		//cout << "Camera pos: " << camera.position().x << " " << camera.position().y << " " << camera.position().z << " front: " << camera.Front.x << " " << camera.Front.y << " " << camera.Front.z << endl;
		window->Update();
		shader.resetLights();
		//glwSpotLight slight(vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), camera.position(), camera.Front, 0.0f,30.0f);
		//shader.addSpotLight(slight);
		glwPointLight pLight(vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), camera.position());
		shader.addPointLight(pLight);

		//processInput(window);
		glClearColor(0.1f, 0.2f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glwProjection projection(SCR_WIDTH, SCR_HEIGHT, camera.Zoom);
		projection.PreDraw(shader);
		shader.setCamera(camera);
		shader.setProjection(projection);
		//suit->Translate(vec3(0.01f, 0.0f, 0.0f));
		race_track->Draw(shader);
		car->Draw(shader);
		window->SwapBuffers();
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

static void processInput(glwWindow & window, const FrameUpdateInfo& info)
{
	if (window.GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
		window.SetShouldClose(true);
}