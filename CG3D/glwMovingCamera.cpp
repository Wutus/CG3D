#include "glwMovingCamera.h"

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


glwMovingCamera::glwMovingCamera(vec3 pos) : glwCamera(pos), Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	InitDefaults();
}

glwMovingCamera::glwMovingCamera(vec3 pos, vec3 target) : glwCamera(pos, target), Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	InitDefaults();
}

glwMovingCamera::glwMovingCamera(vec3 pos, std::shared_ptr<glwObject3D> target) : glwCamera(pos, target), Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	InitDefaults();
}

void glwMovingCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		_pos += Front * velocity;
	if (direction == BACKWARD)
		_pos -= Front * velocity;
	if (direction == LEFT)
		_pos -= Right * velocity;
	if (direction == RIGHT)
		_pos += Right * velocity;

	_model = glm::lookAt(_pos, _pos + Front, Up);
}

void glwMovingCamera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();

	_model = glm::lookAt(_pos, _pos + Front, Up);
}

void glwMovingCamera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;

	_model = glm::lookAt(_pos, _pos + Front, Up);
}

glwMovingCamera::~glwMovingCamera()
{
}

void glwMovingCamera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, up));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));
}

void glwMovingCamera::InitDefaults()
{
	Yaw = YAW;
	Pitch = PITCH;
	updateCameraVectors();
}
