#pragma once
#include "glwObject3D.h"
#include "glwDirectionalLight.h"
#include "glwSpotLight.h"
#include "glwPointLight.h"
#include "glwCompoundObject3D.h"
#include "glwCamera.h"
#include "glwAdvancedShader.h"
#include "glwProjection.h"

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
	void SetShader(std::shared_ptr<glwAdvancedShader> shader);
	void SetProjection(std::shared_ptr<glwProjection> projection);
	void Draw();
	void SaveToFile(const std::string & fileName);
	std::string name;
private:
	std::shared_ptr<glwCamera> camera;
	std::shared_ptr<glwAdvancedShader> shader;
	std::shared_ptr<glwProjection> projection;
};

