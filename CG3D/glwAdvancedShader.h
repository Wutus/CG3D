#pragma once
#include "glwShader.h"
#include "glwCamera.h"
#include "glwPointLight.h"
#include "glwDirectionalLight.h"
#include "glwSpotLight.h"
#include <memory>
#include <string>

class glwAdvancedShader :
	public glwShader
{
public:
	glwAdvancedShader(std::string vertexPath, std::string fragmentPath);
	~glwAdvancedShader();
	void setCamera(const glwCamera & camera);
	void addPointLight(const glwPointLight & pointLight);
	void addSpotLight(const glwSpotLight & pointLight);
	void addDirectionalLight(const glwDirectionalLight & pointLight);
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

