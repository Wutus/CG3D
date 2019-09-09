#pragma once
#include "glwLightSource.h"
#include "glwBaseSerialization.hpp"
#include <boost/serialization/version.hpp>
#include <boost/serialization/access.hpp>

class glwDirectionalLight :	public glwLightSource
{
public:
	glwDirectionalLight(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular, vec3 dir = vec3(0.0f, -1.0f, 0.0f));
	~glwDirectionalLight();
	vec3 direction;

	virtual void PreDraw(glwAdvancedShader & shader, mat4x4 model = mat4x4(1.0f)) override;
protected:
	glwDirectionalLight() = default;
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<glwLightSource>(*this);
		ar & direction;
	};
};

