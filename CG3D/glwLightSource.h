#pragma once
#include "glwPreDrawable.h"
#include "glm/gtc/type_ptr.hpp"
#include "glwBaseSerialization.hpp"
#include <boost/serialization/version.hpp>
#include <boost/serialization/access.hpp>

using namespace glm;

class glwLightSource : public glwPreDrawable
{
public:
	glwLightSource(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular);
	~glwLightSource();
	vec3 color;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	// Inherited via glwPreDrawable
	virtual void PreDraw(glwAdvancedShader & shader, mat4x4 model = mat4x4(1.0f)) = 0;
protected:
	glwLightSource() = default;
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<glwPreDrawable>(*this);
		ar & color;
		ar & ambient;
		ar & diffuse;
		ar & specular;
	};
};

