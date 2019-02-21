#pragma once
#include "glwObject3D.h"
#include "glwDirectionalLight.h"
#include "glwSpotLight.h"
#include "glwPointLight.h"
#include "glwCompoundObject3D.h"
#include "glwCamera.h"
#include "glwAdvancedShader.h"

#include <string>
#include <memory>

class glwScene
{
public:
	glwScene(const std::string & name);
	~glwScene();
	static std::shared_ptr<glwScene> LoadFromFile(const std::string & fileName);
	glwCompoundObject3D Objects;
	std::vector<std::shared_ptr<glwDirectionalLight>> dirLights;
	std::vector<std::shared_ptr<glwSpotLight>> spotLights;
	std::vector<std::shared_ptr<glwPointLight>> pointLights;
	void SetCamera(std::shared_ptr<glwCamera> camera);
	void SetLightShader(std::shared_ptr<glwShader> lightshader);
	void SetShader(std::shared_ptr<glwAdvancedShader> shader);
	void Draw();
	void SaveToFile(const std::string & fileName);
	std::string name;
private:

};

