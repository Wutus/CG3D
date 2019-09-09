#pragma once
#include "glwLightSource.h"
#include "glwObject3D.h"
#include "glwBaseSerialization.hpp"
#include <boost/serialization/version.hpp>
#include <boost/serialization/access.hpp>

class glwPointLight : public glwLightSource, public glwObject3D
{
public:
	glwPointLight(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular, vec3 pos, const std::string & name = "", vec3 distanceFactor = vec3(1.0f,0.0f,0.0f));
	~glwPointLight();
	virtual glwPointLight *Clone(const std::string & name = "") override;
	vec3 distanceFactor;

	// Inherited via glwLightSource
	virtual void PreDraw(glwAdvancedShader & shader, mat4x4 model = mat4x4(1.0f)) override;
protected:
	glwPointLight() = default;
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<glwLightSource>(*this);
		ar & boost::serialization::base_object<glwObject3D>(*this);
		ar & distanceFactor;
	};
};

