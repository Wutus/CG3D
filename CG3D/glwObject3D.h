#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class glwObject3D
{
public:
	glwObject3D(vec3 pos);
	glwObject3D(const glwObject3D &) = delete;
	virtual ~glwObject3D();
	const vec3 & position() const;
	const mat4x4 & model() const;
	void Rotate(float degrees, vec3 axis);
	void Translate(vec3 translation);
	void Scale(vec3 coef);
protected:
	mat4x4 _model;
	vec3 _pos;
};
