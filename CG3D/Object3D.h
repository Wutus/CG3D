#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class Object3D
{
public:
	Object3D(vec3 position);
	Object3D(vec3 position, mat4x4 internal);
	virtual ~Object3D();
	vec3 position;
	mat4x4 internal;
	mat4x4 model;
	void Rotate(float degrees, vec3 axis);
	void Translate(vec3 translation);
	void Scale(vec3 coef);
};

