#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "glwBaseSerialization.hpp"
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/access.hpp>
#include <string>

using namespace glm;

class glwObject3D
{
public:
	glwObject3D(vec3 pos, const std::string & name = "");
	glwObject3D(const glwObject3D &) = delete;
	virtual ~glwObject3D();
	virtual glwObject3D *Clone(const std::string & name = "");
	const vec3 & position() const;
	const mat4x4 & model() const;
	void Rotate(float degrees, vec3 axis);
	void Translate(vec3 translation);
	void Scale(vec3 coef);
	void Reset();
	std::string name;
protected:
	glwObject3D();
	mat4x4 _model;
	vec3 _pos;
private:
	static unsigned int counter;
	static std::string getNewName();

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & name;
		ar & _model;
		ar & _pos;
	};
};

