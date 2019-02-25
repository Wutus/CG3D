#pragma once
#include "glwShader.h"
#include "glwCamera.h"
#include "glwPointLight.h"
#include "glwDirectionalLight.h"
#include "glwSpotLight.h"
#include "glwProjection.h"
#include "glwMaterial.h"

#include "glm/gtc/type_ptr.hpp"

#include <memory>
#include <string>

class glwAdvancedShader :
	public glwShader
{
public:
	glwAdvancedShader(std::string vertexPath, std::string fragmentPath);
	~glwAdvancedShader();
	void setCamera(const glwCamera & camera, mat4x4 system = mat4x4(1.0f));
	void addPointLight(const glwPointLight & pointLight, mat4x4 system = mat4x4(1.0f));
	void addSpotLight(const glwSpotLight & spotLight, mat4x4 system = mat4x4(1.0f));
	void addDirectionalLight(const glwDirectionalLight & dirLight);
	void setProjection(const glwProjection & projection);
	void setModelMatrix(const mat4x4 & model);
	void setMaterial(const glwMaterial & material);
	void resetLights();
private:
	int pointlights;
	int spotlights;
	int dirlights;
	void addLightSource(string lightPath, const glwLightSource & lightSource);
	enum LIGHTTYPE {
		POINTLIGHT,
		SPOTLIGHT,
		DIRLIGHT
	};
	string getLightPath(LIGHTTYPE type);
};

