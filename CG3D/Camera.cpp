#include "Camera.h"

const vec3 up = vec3(0.0f, 1.0f, 0.0f);

Camera::Camera(vec3 pos) : Object3D(pos)
{
}

Camera::Camera(vec3 pos, vec3 target) : Object3D(pos)
{
	model = glm::lookAt(pos, target, up);
}

Camera::Camera(vec3 pos, Object3D target) : Object3D(pos)
{
	model = glm::lookAt(pos, vec3(target.position), up);
}

Camera::~Camera()
{
}

void Camera::LookAt(Object3D target)
{
	model = glm::lookAt(vec3(position), vec3(target.position), up);
}

void Camera::LookAt(vec3 target)
{
	model = glm::lookAt(vec3(position), vec3(target), up);
}
