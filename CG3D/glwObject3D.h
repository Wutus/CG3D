#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>

using namespace glm;

class glwObject3D
{
public:
	glwObject3D(vec3 pos, const std::string & name = "");
	glwObject3D(const glwObject3D &) = delete;
	virtual ~glwObject3D();
	const vec3 & position() const;
	const mat4x4 & model() const;
	void Rotate(float degrees, vec3 axis);
	void Translate(vec3 translation);
	void Scale(vec3 coef);
	std::string name;
protected:
	mat4x4 _model;
	vec3 _pos;
private:
	static unsigned int counter;
	static std::string getNewName();
};

