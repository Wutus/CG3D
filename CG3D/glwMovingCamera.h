#pragma once
#include "glwCamera.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <memory>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class glwMovingCamera :
	public glwCamera
{
public:
	glwMovingCamera(vec3 pos);
	glwMovingCamera(vec3 pos, vec3 target);
	glwMovingCamera(vec3 pos, std::shared_ptr<glwObject3D> target);
	
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);

	~glwMovingCamera();

	glm::vec3 Front;
	float Zoom;
private:
	void updateCameraVectors();
	void InitDefaults();

	glm::vec3 Up;
	glm::vec3 Right;
	// Euler Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
};

