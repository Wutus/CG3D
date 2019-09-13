#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glwAdvancedShader.h"
#include "glwWindow.h"
#include "glwFreeCamera.h"
#include "glwProjection.h"
#include "glwModelObject3D.h"
#include "glwCarDriver.h"
#include "glwCompoundObject3D.h"

#include <utility>
#include <iostream>

using namespace std;

static void processInput(glwWindow & window, const FrameUpdateInfo& info);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

bool freec = false;
bool day = true;

int main()
{
	shared_ptr<glwWindow> window = make_shared<glwWindow>(SCR_WIDTH, SCR_HEIGHT, "CG3D");
	shared_ptr<glwAdvancedShader> shader, gouraud, phong;
	phong = make_shared< glwAdvancedShader>("phong.vs", "phong.fs");
	gouraud = make_shared<glwAdvancedShader>("gouraud.vs", "gouraud.fs");
	shader = phong;
	shared_ptr<glwFreeCamera> freecamera = make_shared<glwFreeCamera>(vec3(-1.7f, 1.0f, -39.0f), window, "free_camera");
	shared_ptr<glwCamera> camera = make_shared<glwCamera>(vec3(-2.0f, 2.0f, 0.0f),vec3(0.0f, 1.0f, 0.0f), "camera");

	glEnable(GL_DEPTH_TEST);

	//glwDirectionalLight dLight(vec3(0.0f, 1.0f, 0.0f), vec3(0.01f, 0.01f, 0.01f), vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, -0.2f, 1.0f));
	//glwDirectionalLight dLight(vec3(0.1f, 0.1f, 0.1f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f));

	window->frameUpdateEvent += processInput;

	shared_ptr<glwModel> race_track_model = make_shared<glwModel>("resources/track2/track01_.3ds");
	shared_ptr<glwModelObject3D> race_track = make_shared<glwModelObject3D>(race_track_model, vec3(0.0f), "race_track", rotate(scale(mat4x4(1.0f), vec3(0.08f)), radians(270.0f), vec3(1.0f, 0.0f, 0.0f)));

	shared_ptr<glwModel> car_model = make_shared<glwModel>("resources/car_models/car_red.obj");
	shared_ptr<glwModelObject3D> raw_car = make_shared<glwModelObject3D>(car_model, vec3(-1.7f, 0.0f, -39.0f), "car", rotate(scale(mat4x4(1.0f), vec3(0.05f,0.05f,0.05f)), radians(90.0f), vec3(0.0f,1.0f,0.0f)));
	shared_ptr<glwCompoundObject3D> car = make_shared<glwCompoundObject3D>(raw_car);
	shared_ptr<glwModel> plane_model = make_shared<glwModel>("resources/plane/plane.obj");
	shared_ptr<glwModelObject3D> plane = make_shared<glwModelObject3D>(plane_model, vec3(0.0f, -0.25f, 0.0f), "plane", rotate(mat4x4(1.0f), radians(0.0f), vec3(1.0f, 0.0f, 0.0f)));
	//car->Rotate(90.0, vec3(0.0, 1.0, 0.0));
	car->AddObject(camera);
	shared_ptr<glwPointLight> plight = make_shared<glwPointLight>(vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.5f, 0.5f, 0.5f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.5f, 0.0f));
	//shader.addSpotLight(slight);
	car->AddObject(plight);
	//camera->LookAt(raw_car);
	//camera.LookAt(suit);
	shader->use();
	glwCarDriver driver(window, car);
	//shader.addSpotLight(sLight);

	while (!window->ShouldClose())
	{
		/*cout << "\rCamera pos: " << freecamera->position().x << " " << freecamera->position().y << " " << freecamera->position().z << 
			" front: " << freecamera->Front.x << " " << freecamera->Front.y << " " << freecamera->Front.z << endl;*/
		cout << driver.velocity << "m/s " << driver.acceleration << "m/s^2" << endl;
		window->Update();
		shader->resetLights();
		//glwPointLight pLight(vec3(1.0f, 1.0f, 1.0f), vec3(0.1f, 0.1f, 0.1f), vec3(0.1f, 0.1f, 0.1f), vec3(0.1f, 0.1f, 0.1f), camera->position());
		//shader->addPointLight(pLight);

		//processInput(window);
		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glwProjection projection(SCR_WIDTH, SCR_HEIGHT, 90/*camera.Zoom*/); 
		projection.PreDraw(*shader);
		shader->setProjection(projection);
		//plight->PreDraw(*shader);
		car->PreDraw(*shader);
		freecamera->Freeze = !freec;
		if (freec)
		{
			freecamera->PreDraw(*shader);
		}
		
		plane->Draw(*shader);
		race_track->Draw(*shader);
		car->Draw(*shader);
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

	if (window.GetKey(GLFW_KEY_F10) == GLFW_PRESS)
		freec = false;

	if (window.GetKey(GLFW_KEY_F11) == GLFW_PRESS)
		freec = true;

	if (window.GetKey(GLFW_KEY_1) == GLFW_PRESS)
		day = true;

	if (window.GetKey(GLFW_KEY_2) == GLFW_PRESS)
		day = false;
}