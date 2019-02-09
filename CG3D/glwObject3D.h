#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class glwObject3D
{
public:
	glwObject3D();
	glwObject3D(const glwObject3D &) = delete;
	virtual ~glwObject3D();
	virtual vec3 & position() = 0;
	virtual mat4x4 & model() = 0;
	void Rotate(float degrees, vec3 axis);
	void Translate(vec3 translation);
	void Scale(vec3 coef);
};

