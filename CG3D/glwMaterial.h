#pragma once

#include "glm/gtc/type_ptr.hpp"
#include "glwTexture2D.h"
#include <memory>

using namespace glm;

class glwMaterial
{
public:
	glwMaterial(std::shared_ptr<glwTexture2D> ambientTexture, std::shared_ptr<glwTexture2D> diffuseTexture, std::shared_ptr<glwTexture2D> specularTexture = nullptr, float shininess = 1.0f);
	~glwMaterial();
	const std::shared_ptr<glwTexture2D> getAmbientTexture() const;
	const std::shared_ptr<glwTexture2D> getDiffuseTexture() const;
	const std::shared_ptr<glwTexture2D> getSpecularTexture() const;
	void setAmbientTexture(std::shared_ptr<glwTexture2D> ambientTexture);
	void setDiffuseTexture(std::shared_ptr<glwTexture2D> diffuseTexture);
	void setSpecularTexture(std::shared_ptr<glwTexture2D> specularTexture);
	float shininess;
private:
	std::shared_ptr<glwTexture2D> ambientTexture;
	std::shared_ptr<glwTexture2D> diffuseTexture;
	std::shared_ptr<glwTexture2D> specularTexture;
	std::shared_ptr<glwTexture2D> normalTexture;
	std::shared_ptr<glwTexture2D> heightTexture;
	bool checkNull();
	static std::shared_ptr<glwTexture2D> defaultTexture;
};

