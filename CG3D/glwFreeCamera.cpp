#include "glwFreeCamera.h"

#include "glwAdvancedShader.h"
#include "glwDefines.h"
// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


glwFreeCamera::glwFreeCamera(vec3 pos, std::shared_ptr<glwWindow> window, const std::string & name) : glwCamera(pos, name), Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	InitDefaults();
	connectToEvents(window);
}

glwFreeCamera::glwFreeCamera(vec3 pos, vec3 target, std::shared_ptr<glwWindow> window, const std::string & name) : glwCamera(pos, target, name), Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	InitDefaults();
	connectToEvents(window);
}

glwFreeCamera::glwFreeCamera(vec3 pos, std::shared_ptr<glwObject3D> target, std::shared_ptr<glwWindow> window, const std::string & name) : glwCamera(pos, target, name), Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	InitDefaults();
	connectToEvents(window);
}

void glwFreeCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	if (Freeze)
		return;
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

void glwFreeCamera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	if (Freeze)
		return;
	yoffset *= -1; 
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

void glwFreeCamera::ProcessMouseScroll(float yoffset)
{
	if (Freeze)
		return;
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;

	_model = glm::lookAt(_pos, _pos + Front, Up);
}

void glwFreeCamera::PreDraw(glwAdvancedShader & shader, mat4x4 model)
{
	shader.setMat4(VIEW, model * _model);
	shader.setVec3(VIEWPOS, _pos);
}

glwFreeCamera::~glwFreeCamera()
{
	std::shared_ptr<glwWindow> w = win.lock();
	w->mouseMoveEvent -= mouseMoveCb;
	w->scrollEvent -= scrollCb;
	w->frameUpdateEvent -= updateCb;
}

void glwFreeCamera::updateCameraVectors()
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

void glwFreeCamera::InitDefaults()
{
	Yaw = YAW;
	Pitch = PITCH;
	updateCameraVectors();
	_model = glm::lookAt(_pos, _pos + Front, Up);
}

void glwFreeCamera::connectToEvents(std::shared_ptr<glwWindow> window)
{
	win = window;
	mouseMoveCb = [this](glwWindow & w, const CursorPos & cp) {this->ProcessMouseMovement(static_cast<float>(cp.x), static_cast<float>(cp.y)); };
	scrollCb = [this](glwWindow & w, const ScrollOffset & so) {this->ProcessMouseScroll(static_cast<float>(so.y)); };
	updateCb = [this](glwWindow & w, const FrameUpdateInfo & info) {
		if (w.GetKey(GLFW_KEY_W) == GLFW_PRESS)
			this->ProcessKeyboard(FORWARD, info.DeltaTime);
		if (w.GetKey(GLFW_KEY_S) == GLFW_PRESS)
			this->ProcessKeyboard(BACKWARD, info.DeltaTime);
		if (w.GetKey(GLFW_KEY_A) == GLFW_PRESS)
			this->ProcessKeyboard(LEFT, info.DeltaTime);
		if (w.GetKey(GLFW_KEY_D) == GLFW_PRESS)
			this->ProcessKeyboard(RIGHT, info.DeltaTime);
	};

	window->mouseMoveEvent += mouseMoveCb;
	window->scrollEvent += scrollCb;
	window->frameUpdateEvent += updateCb;
}
