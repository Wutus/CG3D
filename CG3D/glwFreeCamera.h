#pragma once
#include "glwCamera.h"

#include <vector>
#include <memory>
#include <functional>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glwWindow.h"

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class glwFreeCamera :
	public glwCamera
{
public:
	glwFreeCamera(vec3 pos, glwWindow & window);
	glwFreeCamera(vec3 pos, vec3 target, glwWindow & window);
	glwFreeCamera(vec3 pos, std::shared_ptr<glwObject3D> target, glwWindow & window);

	bool Freeze;

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);

	~glwFreeCamera();

	glm::vec3 Front;
	float Zoom;
private:
	void updateCameraVectors();
	void InitDefaults();
	void connectToEvents(glwWindow & window);
	std::function<void(glwWindow&, const CursorPos&)> mouseMoveCb;
	std::function<void(glwWindow&, const ScrollOffset&)> scrollCb;
	std::function<void(glwWindow&, const FrameUpdateInfo&)> updateCb;;

	glm::vec3 Up;
	glm::vec3 Right;
	// Euler Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;

	glwWindow *win;
};

