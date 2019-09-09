#pragma once
#include "glwShader.h"
#include "glwCamera.h"
#include "glwPointLight.h"
#include "glwDirectionalLight.h"
#include "glwSpotLight.h"
#include "glwProjection.h"
#include "glwMaterial.h"

#include "glm/gtc/type_ptr.hpp"

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/access.hpp>

#include <memory>
#include <string>

using namespace glm;

class glwAdvancedShader : public glwShader
{
public:
	glwAdvancedShader(std::string vertexPath, std::string fragmentPath);
	~glwAdvancedShader();
	void addPointLight(const glwPointLight & pointLight, mat4x4 system = mat4x4(1.0f));
	void addSpotLight(const glwSpotLight & spotLight, mat4x4 system = mat4x4(1.0f));
	void addDirectionalLight(const glwDirectionalLight & dirLight);
	void setProjection(const glwProjection & projection);
	void setModelMatrix(const mat4x4 & model);
	void setMaterial(const glwMaterial & material);
	void resetLights();
protected:
	glwAdvancedShader() = default;
private:
	int pointlights;
	int spotlights;
	int dirlights;
	void addLightSource(std::string lightPath, const glwLightSource & lightSource);
	enum LIGHTTYPE {
		POINTLIGHT,
		SPOTLIGHT,
		DIRLIGHT
	};
	std::string getLightPath(LIGHTTYPE type);

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<glwShader>(*this);
		ar & pointlights;
		ar & spotlights;
		ar & dirlights;
	}
};