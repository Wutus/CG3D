#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class Object3D
{
public:
	Object3D(vec4 position);
	Object3D(vec4 position, mat4x4 internal);
	~Object3D();
	vec4 position;
	mat4x4 internal;
	mat4x4 model;
	void Rotate(float degrees, vec3 axis);
	void Translate(vec3 translation);
	void Scale(vec3 coef);
};

